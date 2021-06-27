#include <stdio.h>
#include <stdint.h>//int64_t
void* copy_elements(void *ele_src[], int ele_cnt, size_t ele_size) {
    /* 为ele_cnt个对象申请缓冲区, 每个对象ele_size字节
     * 并从ele_src指定的位置拷贝*/

    void *result = malloc(ele_cnt * ele_size);
    if (result == NULL)
	/* malloc failed */
	return NULL;
    void *next = result;
    int i;
    for (i = 0; i < ele_cnt; i++) {
        /* Copy object i to destination */
        memcpy(next, ele_src[i], ele_size);
        /* Move pointer to next memory region */
        next += ele_size;
    }
    return result;
}

int main()
{
	float xx[100] ;
	//copy_elements(xx,100,sizeof(float));
	int x= 0x80000000;//-2147483648   0xdeadbeef;// 0x12345678;

	printf(" x=%d\n-x=%d\n\n",x,-x);
	
	//getch();
	float f=-123.456;
	int *p=(int*)&f;
	printf("f=%f\n 0x%X\n 0x%X\n\n",f,f,*p);

	int a=-123,b1,b2;
	float f1=a, f2=(unsigned int)a;
	b1 = f1;
	b2 = f2;
	//getch();
	printf("a=%d\nf1=%f, f2=%f\nb1=%d b2=%d\n\n",a,f1,f2,b1,b2);
	
	int n=0xFF7FFFFF;
	int *fp1=(int*)&f1, *fp2=(int*)&f2;
	*fp1=n;
	f2=2*f1;
	printf("code1=0x%X\nf1=%f\n",n,f1);
	printf("code2=0x%X\n2*f1=%f\n2*f1<0=%d\n",*fp2,f2,f2<0);
	return 0;
	
	
	int64_t n2=0;

	short y=x;
	char  z=x;
	//long long  w=x; 
	int64_t w=x;
	printf("x=%x\ny=%x\nz=%x\nw=%I64x\n",x,y,z,w);
	printf("sizeof(char)=%d\nsizeof(short)=%d\nsizeof(int)=%d\nsizeof(long long)=%d\n",
	sizeof(char), sizeof(short), sizeof(int), sizeof(long long) );
}
