#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char* byte_pointer;

typedef struct
{
	int num;
}Student_s;

typedef union
{
	int num;
	char name;
}Student_e;

enum 
{
	Jan = 1, Feb, Mar
}month;

void show_bytes(byte_pointer start, size_t len)
{
	size_t i;
	for (i = 0; i < len; i++)
	{
		printf("%.2x", start[i]);
	}
	printf("\n");
}

show_char(char x)
{
	show_bytes((byte_pointer)&x, sizeof(char));
}

show_short(short x)
{
	show_bytes((byte_pointer)&x, sizeof(short));
}

show_int(int x)
{
	show_bytes((byte_pointer)&x, sizeof(int));
}

show_unsigned(unsigned x)
{
	show_bytes((byte_pointer)&x, sizeof(unsigned));
}

show_long(long x)
{
	show_bytes((byte_pointer)&x, sizeof(long));
}

show_llong(long long x)
{
	show_bytes((byte_pointer)&x, sizeof(long long));
}

show_float(float x)
{
	show_bytes((byte_pointer)&x, sizeof(float));
}

show_double(double x)
{
	show_bytes((byte_pointer)&x, sizeof(double));
}

show_cchar(char *x)
{
	show_bytes((byte_pointer)&x, sizeof(char*));
}
int main()
{
	char c = 'a';
	short st = 1;
	int i = 12;
	unsigned ui = 123;
	long l = 1234;
	long long ll = 12345;
	float f = 3.14;
	double d = 3.1415926;
	char* cc = c;
	Student_s s;
	s.num = 123456;
	Student_e e;
	e.num = 1234567;
	e.name = 'b';
	printf("char类型名:c\t\t内容:%c\t\t地址:%p\t十六进制:", c, &c); show_char(c);
	printf("short类型名:st\t\t内容:%d\t\t地址:%p\t十六进制:", st, &st); show_short(st);
	printf("int类型名:i\t\t内容:%d\t\t地址:%p\t十六进制:", i, &i); show_int(i);
	printf("unsigned类型名:ui\t内容:%u\t地址:%p\t十六进制:", ui, &ui); show_unsigned(ui);
	printf("long类型名:l\t\t内容:%ld\t地址:%p\t十六进制:", l, &l); show_long(l);
	printf("long long类型名:ll\t内容:%lld\t地址:%p\t十六进制:", ll, &ll); show_llong(ll);
	printf("float类型名:f\t\t内容:%f\t地址:%p\t十六进制:", f, &f); show_float(f);
	printf("double类型名:d\t\t内容:%lf\t地址:%p\t十六进制:", d, &d); show_double(d);
	printf("char*类型名:cc\t\t内容:%c\t\t地址:%d\t十六进制:", cc, &cc); show_cchar(cc);
	printf("struct类型名:s.num\t内容:%d\t地址:%d\t十六进制:", s.num, &s); show_int(s.num);
	printf("union类型名:e.num\t内容:%d\t地址:%d\t十六进制:", e.num, &e); show_int(e.num);
	printf("union类型名:e.name\t内容:%c\t\t地址:%d\t十六进制:", e.name, &e); show_int(e.name);
	printf("enum类型名:month\t内容:%d\t\t地址:%p\t十六进制:", month, &month); show_int(month);
	printf("main函数的地址:%lx\n", main);
	printf("printf函数的地址:%lx\n", printf);
}