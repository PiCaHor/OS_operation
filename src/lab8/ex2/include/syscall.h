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

#endif
