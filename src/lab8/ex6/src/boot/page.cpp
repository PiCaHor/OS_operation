#include "os_constant.h"

extern "C" void open_page_mechanism()
{
	int *directory = (int *)PAGE_DIRECTORY;
	int *page = (int *) (PAGE_DIRECTORY + PAGE_SIZE);
	int amount = PAGE_SIZE/4; 

	for(int i=0;i<amount;++i)
	{
		directory[0] = 0; 
		page[0] = 0; 
	}

	int address = 0; 

	for(int i=0;i<256;++i)
	{
		page[i] = address | 0x7; 
		address += PAGE_SIZE; 
	}

	directory[0] = ((int) page) | 0x07; 
	directory[768] = directory[0]; 

	directory[1023] = ((int)directory) | 0x07; 
}
