#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int length(double num)
{
	int len = 0;
	while (num > 0.001)
	{
		num = num / 10;
		len++;
	}
	return len;
}
int main()
{
	double d = 123.456;
	char c[100];
	int n, i,j,p,m=1;
	n = length(d);
	for (j = 0; pow(10, j) < d; j++)
	{
	}
	for (i = 0; i < j; i++)
	{
		c[i] = (((int)d) / ((int)(pow(10, j - i - 1)))) % 10 + '0';
	}
	c[j] = '.';
	for (p= j+1; p< n+1; p++)
	{
		c[p] = ((int)(d * pow(10, m) ))% 10+'0';
		m++;
	}
	c[n+1] = '\0';
	printf("%s\n", c);

    system("pause");
	return 0;
}
