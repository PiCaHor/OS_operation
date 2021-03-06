#include "bitmap.h"
#include "stdlib.h"
#include "stdio.h"

BitMap::BitMap()
{
    initialize(nullptr, 0);
}

void BitMap::initialize(char *bitmap, const int length)
{
    this->bitmap = bitmap;
    this->length = length;

    int bytes = ceil(length, 8);
    for(int i=0;i<bytes; ++i) 
    {
    	bitmap[i] = 0; 
	time[i] = 0; 
    }

}

bool BitMap::get(const int index) const
{
    int pos = index / 8;
    int offset = index % 8;

    return (bitmap[pos] & (1 << offset));
}

void BitMap::set(const int index, const bool status)
{
    int pos = index / 8;
    int offset = index % 8;

    // 清0
    bitmap[pos] = bitmap[pos] & (~(1 << offset));

    // 置1
    if (status)
    {
        bitmap[pos] = bitmap[pos] | (1 << offset);
    }
}

int BitMap::allocate(const int count)
{
    if (count == 0)
        return -1;

    int index, empty, start;

    int best = 999999; 
    int cnt = 0; 
    int tmp = 0; 
    int fl = 0; 

    index = 0;
    while (index < length)
    {
        // 越过已经分配的资源
        while (index < length && get(index))
            ++index;

        // 不存在连续的count个资源
        if (index == length)
            break;  

        // 找到1个未分配的资源
        // 检查是否存在从index开始的连续count个资源
        empty = 0;
	tmp = index; 
        while ((index < length) && (!get(index)) && (empty < count))
        {
            ++empty;
            ++index;
        }

        // 存在连续的count个资源
        if (empty >= count)
        {
	   cnt = index-tmp+1; 
	   if(cnt < best){
	   	fl = 1; 
		best = cnt; 
		start = tmp; 
	   }

	 }
	/*
            for (int i = 0; i < count; ++i)
            {
                set(start + i, true);
            }
            return start;
	    */
    }
    if(fl){
	    for (int i = 0; i < best; ++i)
            {
                set(start + i, true);
            }
            return start;
	}
    return -1;
}

void BitMap::release(const int index, const int count)
{
    for (int i = 0; i < count; ++i)
    {
        set(index + i, false);
    }
    time[index] = 0; 
}

char *BitMap::getBitmap()
{
    return (char *)bitmap;
}

int BitMap::size() const
{
    return length;
}

void BitMap::increase_times(){
	for(int i = 0; i < length; i ++){
	    if(get(i))
		time[i] ++;
	}
}

int BitMap::release_by_time(){
    int max_time = 0;
    int index = 0;
    for(int i = 0; i < length; i ++){
	if(time[i] != 0 && time[i] > max_time){
		max_time = time[i];
		index = i;
	}
	return index;
	}
}
