#ifndef BITMAP_H
#define BITMAP_H

#include "os_type.h"

class BitMap
{
public:
	int length; 
	char *bitmap; 
	int *time; 
public:
	 BitMap(); 
	 void initialize(char *bitmap,const int length); 
	 bool get(const int index) const; 
	 void set(const int index,const bool status); 
	 int allocate(const int count); 
	 void release(const int index,const int count); 
	 char *getBitmap(); 
	 int size() const; 
	 void increase_times(); 
	 int release_by_time(); 
private:
	 BitMap(const BitMap&) {} 
	 void operator = (const BitMap&){}
};

#endif
