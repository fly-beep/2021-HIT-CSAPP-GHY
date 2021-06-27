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
	printf("char������:c\t\t����:%c\t\t��ַ:%p\tʮ������:", c, &c); show_char(c);
	printf("short������:st\t\t����:%d\t\t��ַ:%p\tʮ������:", st, &st); show_short(st);
	printf("int������:i\t\t����:%d\t\t��ַ:%p\tʮ������:", i, &i); show_int(i);
	printf("unsigned������:ui\t����:%u\t��ַ:%p\tʮ������:", ui, &ui); show_unsigned(ui);
	printf("long������:l\t\t����:%ld\t��ַ:%p\tʮ������:", l, &l); show_long(l);
	printf("long long������:ll\t����:%lld\t��ַ:%p\tʮ������:", ll, &ll); show_llong(ll);
	printf("float������:f\t\t����:%f\t��ַ:%p\tʮ������:", f, &f); show_float(f);
	printf("double������:d\t\t����:%lf\t��ַ:%p\tʮ������:", d, &d); show_double(d);
	printf("char*������:cc\t\t����:%c\t\t��ַ:%d\tʮ������:", cc, &cc); show_cchar(cc);
	printf("struct������:s.num\t����:%d\t��ַ:%d\tʮ������:", s.num, &s); show_int(s.num);
	printf("union������:e.num\t����:%d\t��ַ:%d\tʮ������:", e.num, &e); show_int(e.num);
	printf("union������:e.name\t����:%c\t\t��ַ:%d\tʮ������:", e.name, &e); show_int(e.name);
	printf("enum������:month\t����:%d\t\t��ַ:%p\tʮ������:", month, &month); show_int(month);
	printf("main�����ĵ�ַ:%lx\n", main);
	printf("printf�����ĵ�ַ:%lx\n", printf);
}