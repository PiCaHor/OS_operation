#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc,char ** argv)
{
	printf("System call sys_first return %ld\n",syscall(335));
	return 0; 
}
