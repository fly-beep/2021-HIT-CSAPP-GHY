#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main()
{

	float a = 1;
	float b = FLT_TRUE_MIN;

	printf("flaot����0:%f\n", (a / 0));
	printf("flaot���Լ�С������:%f\n", (a / b));

	return 0;
}