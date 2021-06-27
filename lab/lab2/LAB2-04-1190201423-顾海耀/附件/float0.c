#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main()
{

	float a = 1;
	float b = FLT_TRUE_MIN;

	printf("flaot除以0:%f\n", (a / 0));
	printf("flaot除以极小浮点数:%f\n", (a / b));

	return 0;
}