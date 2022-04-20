#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"

STDIO stdio; 
InterruptManager interruptManager;
ProgramManager programManager;

void first_thread(void *arg)
{
   	printf("pid %d name \"%s\": Hello World!\n", programManager.running->pid, programManager.running->name);
	PCB * cur = programManager.running; 
	cur->status = ProgramStatus::DEAD;
	asm_halt(); 
}

void second_thread(void *arg)
{
	printf("pid %d name \"%s\": Second!\n",programManager.running->pid, programManager.running->name); 
	return ;
}

void third_thread(void *arg)
{
        printf("pid %d name \"%s\": third!\n",programManager.running->pid, programManager.running->name);
        return ;
}

extern "C" void setup_kernel()
{
	interruptManager.initialize();
	stdio.initialize(); 
	interruptManager.enableTimeInterrupt(); 
	interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler); 
	programManager.initialize(); 
	
	int pid = programManager.executeThread(first_thread,nullptr,"first thread",1); 
	if(pid == -1) 
	{
		printf("can not execute thread\n"); 
		asm_halt(); 
	}

	int pid1 = programManager.executeThread(third_thread,nullptr,"third thread",1); 

	int pid2 = programManager.executeThread(second_thread,nullptr,"second thread",2);
	ListItem *item = programManager.readyPrograms.front(); 
	PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    	firstThread->status = RUNNING;
    	programManager.readyPrograms.pop_front();
    	programManager.running = firstThread;
    	asm_switch_thread(0, firstThread);
	asm_halt();
}
