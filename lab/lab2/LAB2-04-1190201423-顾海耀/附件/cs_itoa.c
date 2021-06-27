#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int a = 1234;
	char c[100];
	int n,i;
	for ( n = 0; pow(10, n) <a; n++)
	{
	}
	for ( i = 0; i < n; i++)
	{
		c[i] = (a / ((int)(pow(10, n - i - 1))))%10 + '0';
	}
	c[n] = '\0';
	printf("%s\n", c);

    system("pause");
	return 0;
}
