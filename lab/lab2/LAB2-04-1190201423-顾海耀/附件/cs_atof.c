#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double cs_atof(char a[])
{
	int i, length, t;
	double n = 0;
	length = strlen(a);
	for (i = 0; i < length; i++)
	{
		if (a[i] == '.')
		{
			t = i;
			continue;
		}
		n = n * 10 + a[i] - '0';
	}
    n=n * pow(10, (t - length + 1));
	return n;
}

int main()
{
	char a[100] = "123.456";
	printf("%lf\n", cs_atof(a));
    system("pause");
	return 0;
}
