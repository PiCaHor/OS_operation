#ifndef SYSCALL_H
#define SYSCALL_H

#include "os_constant.h"

class SystemService
{
public:
	SystemService(); 
	void initialize(); 
	bool setSystemCall(int index,int function); 
}; 

int syscall_0(int first,int second,int third,int forth,int fifth); 

int write(const char *str);
int syscall_write(const char *str);

int fork(); 
int syscall_fork(); 

void exit(int ret);
void syscall_exit(int ret);

int wait(int *retval);
int syscall_wait(int *retval);
#endif
