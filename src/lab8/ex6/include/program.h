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
	int USER_CODE_SELECTOR; 
	int USER_DATA_SELECTOR;
	int USER_STACK_SELECTOR;

public:
	ProgramManager(); 

	void initialize(); 

	int executeThread(ThreadFunction function,void *parameter, const char *name, int priority); 

	PCB *allocatePCB(); 

	void releasePCB(PCB *program); 

	void schedule(); 
	
	void MESA_WakeUp(PCB *program); 
	
	void initializeTSS();
	
	int executeProcess(const char *filename, int priority); 
	
	int createProcessPageDirectory(); 
	
	bool createUserVirtualPool(PCB *process); 
	
	void activateProgramPage(PCB *program);
	
	int fork(); 
	
	bool copyProcess(PCB *parent,PCB *child); 
	
	void exit(int ret);
	
	int wait(int *retval); 
};

void program_exit(); 
void load_process(const char *filename);
#endif
