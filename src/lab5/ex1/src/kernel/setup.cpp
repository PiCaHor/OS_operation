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
	//asm_enable_interrupt(); 
	printf("print percentage: %%\n"
	      "print char \"N\": %c\n"
	      "print string \"Hello World!\": %s\n"
	      "print decimal: \"-1234\": %d\n"
	      "print hexadecimal \"0x7abcdef0\": %x\n",
	      'N', "Hello World!", -1234, 0x7abcdef0);

	asm_halt();
}
