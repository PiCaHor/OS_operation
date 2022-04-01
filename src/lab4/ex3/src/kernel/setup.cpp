#include "asm_utils.h"
#include "interrupt.h"

InterruptManager interruptManager;

extern "C" void setup_kernel()
{
	interruptManager.initialize();
	int a = 1 / 0;
	asm_halt();
}
