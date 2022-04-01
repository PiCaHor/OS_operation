#ifndef STDIO_H
#define STDIO_H

#include "os_type.h"

class STDIO
{
private:
	uint8 *screen;

public:
	STDIO();
	
	void initialize();
		
	void print(uint x,uint y, uint8 c,uint8 color); 

	void print(uint8 c,uint8 color);

	void print(uint8 c); 

	void moveCursor(uint position);

	void moveCursor(uint x, uint y); 

	uint getCursor();
public:
	void rollUp(); 
}; 

#endif
