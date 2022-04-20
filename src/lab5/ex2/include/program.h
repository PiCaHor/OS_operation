#ifndef PROGRAM_H
#define PROGRAM_H

#include "list.h"
#include "thread.h"

#define ListItem2PCB(ADDRESS, LIST_ITEM) ((PCB *)((int)(ADDRESS) - (int)&((PCB *)0)->LIST_ITEM))

class ProgramManager
{
public:
	List allPrograms; 
	List readyPrograms; 
	PCB * running; 

public:
	ProgramManager(); 

	void initialize(); 

	int executeThread(ThreadFunction function,void *parameter, const char *name, int priority); 

	PCB *allocatePCB(); 

	void releasePCB(PCB *program); 

	void schedule(); 
};

void program_exit(); 

#endif
