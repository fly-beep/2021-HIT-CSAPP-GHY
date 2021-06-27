#include <stdio.h>
#include <stdlib.h>

int IsLittleEndian()
{
	int a = 0x11223344;
	char b = *(char*)&a;
	return (b == 0x44) ? 1 : 0;
}


int main()
{
	printf("%d", IsLittleEndian());
	return 0;
}