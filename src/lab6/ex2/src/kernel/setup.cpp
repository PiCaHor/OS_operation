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

int lag; 
Semaphore space; 
Semaphore num; 
void producer(void *arg)
{
	for(int i = 0; i < 10;++i)
	{
		printf("produce one\n"); 
		space.P(); 
		lag ++; 
		num.V(); 
	}
}

void consumer(void *arg)
{
	for(int i = 0;i<10;++i)
	{
		printf("consumer\n"); 
		num.P(); 
		lag--; 
		space.V();
		int delay= 0xfffffff; 
		while(delay)
		{
			--delay; 
		}
	}

}
Semaphore chopsticks[5]; 
int is_token[5]; 
void philosopher0(void *arg){
	do
	{
		if(is_token[0] ==0 && is_token[1] ==0) {

		printf("NO.0 wants to take the chopstic in his left side.\n");
		chopsticks[0].P();
		is_token[0] = 1; 
		printf("NO.1 successfully took the chopstic in his left side.\n");

		printf("NO.1 wants to take the chopstic in his right side.\n");
		chopsticks[1].P();
		is_token[1] = 1; 
		printf("No.1 successfully took the chopstic in his right side.\n");

		printf("No.1 start eating.\n");
		int delay = 0xfffffff;
		while (delay) --delay;

		printf("No.1 start thinking.\n");
		chopsticks[0].V();
		is_token[0] = 0; 
		chopsticks[1].V();
		is_token[1] = 0; 
		return ; 
		}
	}while(1);
}

void philosopher1(void *arg){
        do
        {
                if(is_token[1] ==0 && is_token[2] ==0) {

                printf("NO.1 wants to take the chopstic in his left side.\n");
                chopsticks[1].P();
                is_token[1] = 1;
                printf("NO.2 successfully took the chopstic in his left side.\n");

                printf("NO.2 wants to take the chopstic in his right side.\n");
                chopsticks[2].P();
                is_token[2] = 1;
                printf("No.2 successfully took the chopstic in his right side.\n");

                printf("No.2 start eating.\n");
                int delay = 0xfffffff;
                while (delay) --delay;

                printf("No.2 start thinking.\n");
                chopsticks[1].V();
                is_token[1] = 0;
                chopsticks[2].V();
                is_token[2] = 0;
                return ;
                }
        }while(1);
}

void philosopher2(void *arg){
        do
        {
                if(is_token[2] ==0 && is_token[3] ==0) {

                printf("NO.2 wants to take the chopstic in his left side.\n");
                chopsticks[2].P();
                is_token[2] = 1;
                printf("NO.3 successfully took the chopstic in his left side.\n");

                printf("NO.3 wants to take the chopstic in his right side.\n");
                chopsticks[3].P();
                is_token[3] = 1;
                printf("No.3 successfully took the chopstic in his right side.\n");

                printf("No.3 start eating.\n");
                int delay = 0xfffffff;
                while (delay) --delay;

                printf("No.3 start thinking.\n");
                chopsticks[2].V();
                is_token[2] = 0;
                chopsticks[3].V();
                is_token[3] = 0;
                return ;
                }
        }while(1);
}

void philosopher3(void *arg){
        do
        {
                if(is_token[3] ==0 && is_token[4] ==0) {

                printf("NO.3 wants to take the chopstic in his left side.\n");
                chopsticks[3].P();
                is_token[3] = 1;
                printf("NO.4 successfully took the chopstic in his left side.\n");

                printf("NO.4 wants to take the chopstic in his right side.\n");
                chopsticks[4].P();
                is_token[4] = 1;
                printf("No.4 successfully took the chopstic in his right side.\n");

                printf("No.4 start eating.\n");
                int delay = 0xfffffff;
                while (delay) --delay;

                printf("No.4 start thinking.\n");
                chopsticks[3].V();
                is_token[3] = 0;
                chopsticks[4].V();
                is_token[4] = 0;
                return ;
                }
        }while(1);
}

void philosopher4(void *arg){
        do
        {
                if(is_token[4] ==0 && is_token[0] ==0) {

                printf("NO.4 wants to take the chopstic in his left side.\n");
                chopsticks[4].P();
                is_token[4] = 1;
                printf("NO.0 successfully took the chopstic in his left side.\n");

                printf("NO.0 wants to take the chopstic in his right side.\n");
                chopsticks[0].P();
                is_token[0] = 1;
                printf("No.0 successfully took the chopstic in his right side.\n");

                printf("No.0 start eating.\n");
                int delay = 0xfffffff;
                while (delay) --delay;

                printf("No.0 start thinking.\n");
                chopsticks[4].V();
                is_token[4] = 0;
                chopsticks[0].V();
                is_token[0] = 0;
                return ;
                }
        }while(1);
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
	for(int i=0;i<5;++i)
	       chopsticks[i].initialize(1); 	
	programManager.executeThread(philosopher0,nullptr,"second thread",1); 
	programManager.executeThread(philosopher1,nullptr,"second thread",1);
	programManager.executeThread(philosopher2,nullptr,"second thread",1);
	programManager.executeThread(philosopher3,nullptr,"second thread",1);
	programManager.executeThread(philosopher4,nullptr,"second thread",1);

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
