#include <stdio.h>
#include <stdlib.h>

int fib_loop(int n)
{
	int x = 1;
	int y = 1;
	
	if (n == 0)
	{
		return 0;
	}
	if (n == 1)
	{
		return 1;
	}
	while (n > 1)
	{
		int z = x + y;
		x = y;
		y = z;
		n --;
	}
	return y;
}

int main()
{

	for (int i = 0; i < 100; i++)
	{
		printf("%d\t%d\n", i + 1, fib_loop(i));
	}
	return 0;
}