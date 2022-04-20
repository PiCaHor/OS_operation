#include "os_type.h"

template<typename T>
void swap(T &a,T &b){
	T c = a; 
	a = b; 
	b = c; 
}

void itos(char *numStr, uint32 num, uint32 mod) {
    if (mod < 2 || mod > 26 || num < 0) {
        return;
    }

    uint32 length, temp;

    length = 0;
    while(num) {
        temp = num % mod;
        num /= mod;
        numStr[length] = temp > 9 ? temp - 10 + 'A' : temp + '0';
        ++length;
    }

    if(!length) {
        numStr[0] = '0';
        ++length;
    }

    for(int i = 0, j = length - 1; i < j; ++i, --j) {
        swap(numStr[i], numStr[j]);
    }

    numStr[length] = '\0';
}
