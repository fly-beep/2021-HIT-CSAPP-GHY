#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int utf8len(char* a);

int main()
{
	int word = 0;
	char str[1000], * p;
	strcpy(str,"顾海耀");
	p = str;
	word = utf8len(p);
	printf("%d\n", word);
	return 0;
}

int utf8len(char* a)
{
	int word = 0;
	int len = 0;
	for (int i = 0; a[i] != '\0'; i += len) {
		unsigned char byte = a[i];
		if (byte >= 0xFC)
			len = 6;
		else if (byte >= 0xF8)
			len = 5;
		else if (byte >= 0xF0)
			len = 4;
		else if (byte >= 0xE0)
			len = 3;
		else if (byte >= 0xC0)
			len = 2;
		else
			len = 1;
		word++;
	}
	return word;
}
