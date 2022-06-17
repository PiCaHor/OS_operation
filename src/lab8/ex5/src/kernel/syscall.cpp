#include "syscall.h"
#include "interrupt.h"
#include "stdlib.h"
#include "asm_utils.h"
#include "os_modules.h"
#include "stdio.h"
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

int write(const char *str) {
    	return asm_system_call(1, (int)str);
}

int syscall_write(const char *str) {
    	return stdio.print(str);
}


int fork()
{
	return asm_system_call(2); 
}

int syscall_fork()
{
	return programManager.fork(); 
}

void exit(int ret) {
    	asm_system_call(3, ret);
}

void syscall_exit(int ret) {
    	programManager.exit(ret);
}
