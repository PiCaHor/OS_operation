#include "interrupt.h"
#include "os_type.h"
#include "os_constant.h"
#include "asm_utils.h"
#include "stdio.h"
#include "os_modules.h"
#include "program.h"
extern STDIO stdio; 
int times = 0; 

InterruptManager::InterruptManager()
{
	initialize();
}

void InterruptManager::initialize()
{	
	times = 0; 
	IDT  = (uint32 *)IDT_START_ADDRESS;
	asm_lidt(IDT_START_ADDRESS, 256 * 8 - 1); 

	for(uint i = 0; i < 256; ++i)
	{
		setInterruptDescriptor(i, (uint32)asm_unhandled_interrupt, 0); 
	}

	initialize8259A(); 
}


void InterruptManager::setInterruptDescriptor(uint32 index, uint32 address, byte DPL)
{
	IDT[index * 2] = (CODE_SELECTOR << 16) | (address & 0xffff);
	IDT[index * 2 + 1] = (address & 0xffff0000) | (0x1 << 15) | (DPL << 13) | (0xe << 8); 
}

void InterruptManager::initialize8259A()
{
	asm_out_port(0x20,0x11); 
	asm_out_port(0xa0,0x11);

	IRQ0_8259A_MASTER = 0X20; 
	IRQ0_8259A_SLAVE = 0X28; 

	asm_out_port(0x21,IRQ0_8259A_MASTER); 
	asm_out_port(0xa1,IRQ0_8259A_SLAVE); 

	asm_out_port(0X21,4);
	asm_out_port(0xa1,2); 

	asm_out_port(0x21,1); 
	asm_out_port(0xa1,1); 

	asm_out_port(0x21,0xfb); 
	asm_out_port(0xa1,0xff); 
}

void InterruptManager::enableTimeInterrupt()
{
	uint8 value;
	asm_in_port(0x21,&value); 

	value = value & 0xfe; 
       	asm_out_port(0x21,value); 	
}

void InterruptManager::disableTimeInterrupt()
{
	uint8 value; 
	asm_in_port(0x21,&value);

	value = value & 0x01; 
	asm_out_port(0x21,value); 
}

void InterruptManager::setTimeInterrupt(void *handler)
{
    setInterruptDescriptor(IRQ0_8259A_MASTER, (uint32)handler, 0);
}

extern "C" void c_time_interrupt_handler()
{
        PCB *cur = programManager.running;
	/*
    	if (cur->status != ProgramStatus::DEAD)
    	{
        	--cur->ticks;
        	++cur->ticksPassedBy;
    	}
    	else
    	{
        	programManager.schedule();
    	}
	*/
	if(cur->status == ProgramStatus::DEAD)
		programManager.schedule();
}

void InterruptManager::enableInterrupt()
{
	asm_enable_interrupt(); 
}

void InterruptManager::disableInterrupt()
{
	asm_disable_interrupt(); 
}

bool InterruptManager::getInterruptStatus()
{
	return asm_interrupt_status()? true:false; 
}

void InterruptManager::setInterruptStatus(bool status)
{
	if(status) enableInterrupt();
	else disableInterrupt(); 
}
