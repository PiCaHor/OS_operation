#ifndef MEMORY_H
#define MEMORY_H

#include "address_pool.h"

enum AddressPoolType
{
	USER,
	KERNEL
}; 

class MemoryManager
{
public:
	int totalMemory; 

	AddressPool kernelPhysical; 

	AddressPool userPhysical; 

	AddressPool kernelVirtual; 
public:
	MemoryManager(); 

	void initialize(); 

	int allocatePhysicalPages(enum AddressPoolType type,const int count); 

	void releasePhysicalPages(enum AddressPoolType type,const int paddr, const int count); 

	int getTotalMemory();
    
	void openPageMechanism();
	
	int allocatePages(enum AddressPoolType type,const int count); 
	
	int allocateVirtualPages(enum AddressPoolType type, const int count); 
	
	bool connectPhysicalVirtualPage(const int virtualAddress, const int physicalPageAddress); 
	
	void releasePages(enum AddressPoolType type, const int virtualAddress, const int count); 
	int vaddr2paddr(int vaddr);
	
	void releaseVirtualPages(enum AddressPoolType type, const int vaddr, const int count); 
};

#endif
