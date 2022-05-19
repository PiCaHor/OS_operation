#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"

STDIO stdio; 
InterruptManager interruptManager;
ProgramManager programManager;
SpinLock aLock;
Semaphore semaphore;

int cheese_burger; 

void a_mother(void *arg)
{	
	 semaphore.P(); 
	 int delay = 0; 

	 printf("mother:start to make cheese burger, there are %d cheese burger now\n",cheese_burger); 

	 cheese_burger += 10; 

	 printf("mother: oh, I have to hang clothe out.\n"); 

	 delay = 0xfffffff; 
	 while(delay)
	 	--delay; 

	 printf("mother:Oh, Jesus! There are %d cheese burgers\n",cheese_burger);
	 semaphore.V();  
}

void a_naughty_boy(void *arg)
{
	semaphore.P(); 
	printf("boy: Look what I found!\n");

	cheese_burger -= 10;	
	semaphore.V(); 
}

void first_thread(void *arg)
{
	semaphore.initialize(1); 
   	stdio.moveCursor(0); 
	for(int i = 0;i<25*80;++i)
	{
		stdio.print(' '); 
	}
	stdio.moveCursor(0); 
	cheese_burger = 0; 
	programManager.executeThread(a_mother,nullptr,"second thread",1); 
	programManager.executeThread(a_naughty_boy,nullptr,"third thread",1); 
	asm_halt(); 
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

	ListItem *item = programManager.readyPrograms.front(); 
	PCB *firstThread = ListItem2PCB(item, tagInGeneralList);
    	firstThread->status = RUNNING;
    	programManager.readyPrograms.pop_front();
    	programManager.running = firstThread;
    	asm_switch_thread(0, firstThread);
	asm_halt();
}
