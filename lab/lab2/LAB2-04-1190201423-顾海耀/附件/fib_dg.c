#include <stdio.h>
#include <stdlib.h>

int fib_dg(int n)
{
	if (n == 0)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	else
	{
		return fib_dg(n - 1) + fib_dg(n - 2);
	}
}

int main()
{
	for (int i = 0; i < 100; i++)
	{
		printf("%d:\t%d\n", i + 1, fib_dg(i));
	}
	return 0;
}