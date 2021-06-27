#include <stdio.h>
#include <stdlib.h>

int CpuWordSize()
{
	return sizeof(int*) * sizeof(int*);
}

int main()
{
	printf("CpuWordSize is %d\n", CpuWordSize());
	return 0;
}