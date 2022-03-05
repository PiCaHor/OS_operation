#include <stdio.h>

extern void print(); 	// function from cfn.asm

void init()
{
	freopen("hello.txt","r",stdin);	// relocate the file  
	freopen("hello1.txt","w",stdout); 
	char s[20]; 
	scanf("%s",s);	// read 
	printf("%s",s); // write
	freopen("/dev/tty/", "w", stdout); // relocate to the command line
	printf("%s",s); 
	fclose(stdin);
    	fclose(stdout);
}

int main()
{
	print(); 
	return 0; 
}

