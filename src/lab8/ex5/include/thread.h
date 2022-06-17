#ifndef THREAD_H
#define THREAD_H

#include "list.h"
#include "os_constant.h"
#include "address_pool.h"

typedef void (*ThreadFunction)(void *);

enum ProgramStatus
{
	CREATED,
	RUNNING,
	READY,
	BLOCKED,
	DEAD
};

struct PCB
{
	int *stack; 
	char name[MAX_PROGRAM_NAME + 1];
	enum ProgramStatus status;
	int priority; 
	int pid;
	int ticks;
	int ticksPassedBy; 
	ListItem tagInGeneralList; 
	ListItem tagInAllList; 
	int pageDirectoryAddress; 
	int parentPid; 
	AddressPool userVirtual; 
	int retValue; 
}; 

#endif
