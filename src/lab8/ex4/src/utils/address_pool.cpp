#include "address_pool.h"
#include "os_constant.h"

AddressPool::AddressPool()
{
}

void AddressPool::initialize(char *bitmap,const int length,const int startAddress)
{
	resources.initialize(bitmap,length); 
	this->startAddress = startAddress; 
}

int AddressPool::allocate(const int count)
{
	uint32 start = resources.allocate(count); 
	return (start == -1)? -1:(start * PAGE_SIZE + startAddress); 
}

void AddressPool::release(const int address,const int amount)
{
	resources.release((address-startAddress) / PAGE_SIZE, amount); 
}
