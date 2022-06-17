#include "asm_utils.h"
#include "interrupt.h"
#include "stdio.h"
#include "program.h"
#include "thread.h"
#include "sync.h"
#include "memory.h"
#include "syscall.h"
#include "tss.h"
STDIO stdio; 
InterruptManager interruptManager;
ProgramManager programManager;
SpinLock aLock;
Semaphore semaphore;
MemoryManager memoryManager; 
SystemService systemService; 
TSS tss; 
int cheese_burger; 

int syscall_0(int first, int second, int third, int forth, int fifth)
{
	printf("systerm call 0: %d, %d, %d, %d, %d\n",
		first, second, third, forth, fifth);
	return first + second + third + forth + fifth;
}

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

void thread1(void* arg){
	char *p1;
	p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 2);
	if(!p1){
		printf("thread1 failed to allocate!\n");
 	}
	else{
		printf("thread1 allocate succeed!\n");
	}
	return; 
}
void thread2(void* arg){
	char *p1;
	p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 1);
	if(!p1){
		printf("thread2 failed to allocate!\n");
	}
	else{
		printf("thread2 allocate succeed!\n");	
 	}
	return;
}

void first_process()
{
    	int pid = fork();

    	if (pid == -1)
    	{
        	printf("can not fork\n");
    	}
    	else
    	{
        	if (pid)
        	{
            		printf("I am father, fork reutrn: %d\n", pid);
        	}
        	else
        	{
            		printf("I am child, fork return: %d, my pid: %d\n", pid,programManager.running->pid); 
        	}
    	}
    	asm_halt();
}

void first_thread(void *arg)
{
	/*
	semaphore.initialize(1); 
   	stdio.moveCursor(0); 
	for(int i = 0;i<25*80;++i)
	{
		stdio.print(' '); 
	}
	stdio.moveCursor(0); 
	int memory = *((uint32 *)MEMORY_SIZE_ADDRESS);
    	
    	int low = memory & 0xffff;
    	
    	int high = (memory >> 16) & 0xffff;
    	memory = low * 1024 + high * 64 * 1024;
    	printf("total memory: %d bytes (%d MB)\n", memory, memory / 1024 / 1024);

	char *p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
	char *p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 10);
	char *p3 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
	printf("%x %x %x\n", p1, p2, p3);
	memoryManager.releasePages(AddressPoolType::KERNEL, (int)p2, 10);
	p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 100);
	printf("%x\n", p2);
	p2 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 10);
	printf("%x\n", p2);
	*/
	/*
	 * char *p1,*p2;
	p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 15000);
	int page = 15000;
	while(p1){
		p2 = p1;
		p1 = (char *)memoryManager.allocatePages(AddressPoolType::KERNEL, 1);
		++page;
		printf("%x %d\n", p1,page);
	}
	memoryManager.releasePages(AddressPoolType::KERNEL,(int)p2,1);
	programManager.executeThread(thread1, nullptr, "first thread", 1);
	programManager.executeThread(thread2, nullptr, "second thread", 2);*/
	//printf("start process\n"); 
	//programManager.executeProcess((const char *)first_process, 1);
    	//programManager.executeProcess((const char *)first_process, 1);
    	//programManager.executeProcess((const char *)first_process, 1);
	printf("start process\n");
    	programManager.executeProcess((const char *)first_process, 1);
	asm_halt(); 
}

extern "C" void setup_kernel()
{
	interruptManager.initialize(); 
	interruptManager.enableTimeInterrupt(); 
	interruptManager.setTimeInterrupt((void *)asm_time_interrupt_handler); 

	stdio.initialize(); 
	programManager.initialize(); 
	
//	memoryManager.openPageMechanism(); 
//	memoryManager.initialize();

	systemService.initialize();
	systemService.setSystemCall(0, (int)syscall_0);
	systemService.setSystemCall(1, (int)syscall_write); 
	systemService.setSystemCall(2, (int)syscall_fork); 
/*
	int ret;

	ret = asm_system_call(0);
	printf("return value: %d\n", ret);

	ret = asm_system_call(0, 123);
	printf("return value: %d\n", ret);

	ret = asm_system_call(0, 123, 324);
	printf("return value: %d\n", ret);

	ret = asm_system_call(0, 123, 324, 9248);
	printf("return value: %d\n", ret);

	ret = asm_system_call(0, 123, 324, 9248, 7);
	printf("return value: %d\n", ret);

	ret = asm_system_call(0, 123, 324, 9248, 7, 123);
	printf("return value: %d\n", ret);*/
	
	memoryManager.initialize(); 

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
