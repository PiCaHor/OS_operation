#include "memory.h"
#include "os_constant.h"
#include "stdlib.h"
#include "asm_utils.h"
#include "stdio.h"
#include "program.h"
#include "os_modules.h"

MemoryManager::MemoryManager(){
	initialize(); 
}

void MemoryManager::initialize()
{
	this->totalMemory = 0; 
	this->totalMemory = getTotalMemory(); 
	

	int usedMemory = 256 * PAGE_SIZE + 0x100000;
	if(this->totalMemory < usedMemory)
	{
		printf("memory is too small,halt.\n"); 
		asm_halt(); 
	}

	int freeMemory = this->totalMemory - usedMemory; 

	int freePages = freeMemory / PAGE_SIZE; 
	int kernelPages = freePages / 2; 
	int userPages = freePages - kernelPages; 
	
	int kernelPhysicalStartAddress = usedMemory;
	int userPhysicalStartAddress = usedMemory + kernelPages * PAGE_SIZE;

	int kernelPhysicalBitMapStart = BITMAP_START_ADDRESS;
	int userPhysicalBitMapStart = kernelPhysicalBitMapStart + ceil(kernelPages, 8);
	int kernelVirtualBitMapStart = userPhysicalBitMapStart + ceil(userPages,8); 

	kernelPhysical.initialize((char *)kernelPhysicalBitMapStart, kernelPages, kernelPhysicalStartAddress);
	userPhysical.initialize((char *)userPhysicalBitMapStart, userPages, userPhysicalStartAddress);
	kernelVirtual.initialize((char *)kernelVirtualBitMapStart,kernelPages,KERNEL_VIRTUAL_START); 

	printf("total memory: %d bytes ( %d MB )\n",
        	this->totalMemory,
        	this->totalMemory / 1024 / 1024);

	printf("kernel pool\n"
		"    start address: 0x%x\n"
		"    total pages: %d ( %d MB )\n"
		"    bitmap start address: 0x%x\n",
		kernelPhysicalStartAddress,
		kernelPages, kernelPages * PAGE_SIZE / 1024 / 1024,
		kernelPhysicalBitMapStart);


	printf("user pool\n"
		"    start address: 0x%x\n"
		"    total pages: %d ( %d MB )\n"
		"    bit map start address: 0x%x\n",
		userPhysicalStartAddress,
		userPages, userPages * PAGE_SIZE / 1024 / 1024,
		userPhysicalBitMapStart);
	
	printf("kernel virtual pool\n"
		"    start address: 0x%x\n"
		"    total pages: %d  ( %d MB ) \n"
		"    bit map start address: 0x%x\n",
        	KERNEL_VIRTUAL_START,
		userPages, kernelPages * PAGE_SIZE / 1024 / 1024,
		kernelVirtualBitMapStart);
}

int MemoryManager::getTotalMemory()
{
	if(!this->totalMemory)
	{
		int memory = *((int *) MEMORY_SIZE_ADDRESS); 
		int low = memory  & 0xffff; 
		int high = (memory >> 16) & 0xffff; 

		this->totalMemory = low * 1024 + high * 64 * 1024; 
	} 
	return this -> totalMemory; 
}

int MemoryManager::allocatePhysicalPages(enum AddressPoolType type,const int count)
{
	int start = -1; 

	if (type == AddressPoolType::KERNEL)
	{
		start = kernelPhysical.allocate(count); 
	}
	else if(type == AddressPoolType::USER) 
	{
		start = userPhysical.allocate(count); 
	}
	return (start == -1) ? 0:start; 
}

void MemoryManager::releasePhysicalPages(enum AddressPoolType type,const int paddr,const int count)
{

        if (type == AddressPoolType::KERNEL)
        {
                kernelPhysical.release(paddr,count);
        }
        else if(type == AddressPoolType::USER)
        {
               	userPhysical.release(paddr,count);
        }
}

void MemoryManager::openPageMechanism()
{
	int *directory = (int *)PAGE_DIRECTORY; 

	int *page = (int *)(PAGE_DIRECTORY + PAGE_SIZE); 

	memset(directory,0,PAGE_SIZE); 
	memset(page,0,PAGE_SIZE); 

	int address = 0; 

	for(int i = 0;i<256;++i) 
	{
		page[i] = address | 0x7; 
		address += PAGE_SIZE; 
	}

	directory[0] = ((int)page) | 0x07; 
	directory[768] = directory[0]; 
	directory[1023] = ((int)directory) | 0x7; 

	asm_init_page_reg(directory); 

	printf("open page mechanism\n"); 
}

int MemoryManager::allocatePages(enum AddressPoolType type,const int count)
{
	int virtualAddress = allocateVirtualPages(type,count); 
	if(!virtualAddress)
	{
		return 0; 
	}
	bool flag; 
	int physicalPageAddress; 
	int vaddress = virtualAddress; 

	for(int i = 0; i<count;++i,vaddress += PAGE_SIZE)
	{
		flag = false; 

		physicalPageAddress = allocatePhysicalPages(type,1); 

		if(physicalPageAddress)
		{
			flag = connectPhysicalVirtualPage(vaddress,physicalPageAddress); 
		}
		else 
		{
			flag = false; 
		}

		if(!flag)
		{
			releasePages(type,virtualAddress,i); 
			releaseVirtualPages(type,virtualAddress + i * PAGE_SIZE,count - i); 
			return 0; 
		}
	}
	return virtualAddress; 
}
int MemoryManager::allocateVirtualPages(enum AddressPoolType type, const int count)
{
	int start = -1;

	if (type == AddressPoolType::KERNEL)
	{
		start = kernelVirtual.allocate(count);
	}

	return (start == -1) ? 0 : start;
}

int toPDE(const int virtualAddress)
{
	return (0xfffff000 + (((virtualAddress & 0xffc00000) >> 22) * 4));
}

int toPTE(const int virtualAddress)
{
	return (0xffc00000 + ((virtualAddress & 0xffc00000) >> 10) + (((virtualAddress & 0x003ff000) >> 12) * 4));
}


bool MemoryManager::connectPhysicalVirtualPage(const int virtualAddress, const int physicalPageAddress)
{

	int *pde = (int *)toPDE(virtualAddress);
	int *pte = (int *)toPTE(virtualAddress);

	if(!(*pde & 0x00000001))
	{
		int page = allocatePhysicalPages(AddressPoolType::KERNEL, 1);
		if (!page) return false;

		*pde = page | 0x7;
		char *pagePtr = (char *)(((int)pte) & 0xfffff000);
		memset(pagePtr, 0, PAGE_SIZE);
	}


	*pte = physicalPageAddress | 0x7;

	return true;
}

void MemoryManager::releasePages(enum AddressPoolType type, const int virtualAddress, const int count)
{
	int vaddr = virtualAddress;
	int *pte, *pde;
	bool flag;
	const int ENTRY_NUM = PAGE_SIZE / sizeof(int);

	for (int i = 0; i < count; ++i, vaddr += PAGE_SIZE)
	{
		releasePhysicalPages(type, vaddr2paddr(vaddr), 1);

		pte = (int *)toPTE(vaddr);
		*pte = 0;
	}

	releaseVirtualPages(type, virtualAddress, count);
}

int MemoryManager::vaddr2paddr(int vaddr)
{
	int *pte = (int *)toPTE(vaddr);
	int page = (*pte) & 0xfffff000;
	int offset = vaddr & 0xfff;
	return (page + offset);
}

void MemoryManager::releaseVirtualPages(enum AddressPoolType type, const int vaddr, const int count)
{
	if (type == AddressPoolType::KERNEL)
	{
		kernelVirtual.release(vaddr, count);
	}
}
