#include "syscall.h"
#include "interrupt.h"
#include "stdlib.h"
#include "asm_utils.h"
#include "os_modules.h"

int system_call_table[MAX_SYSTEM_CALL]; 

SystemService::SystemService(){
	initialize(); 
}

void SystemService::initialize()
{
	memset((char *)system_call_table,0,sizeof(int) * MAX_SYSTEM_CALL);
	interruptManager.setInterruptDescriptor(0x80,(uint32)asm_system_call_handler, 3); 
}

bool SystemService::setSystemCall(int index,int function)
{
	system_call_table[index] = function; 
	return true; 
}