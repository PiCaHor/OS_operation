#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"

STDIO stdio; 
InterruptManager interruptManager;

extern "C" void setup_kernel()
{
	interruptManager.initialize();
	stdio.initialize(); 
	interruptManager.enableTimeInterrupt(); 
	interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler); 
	asm_enable_interrupt(); 
	asm_halt();
}
