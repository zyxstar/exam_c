//�0 1 2 3 4 5 6 7  8....
//ֵ��0 1 1 2 3 5 8 13 21............
#include<stdio.h>
unsigned get_fib(unsigned n)
{
	unsigned i=0,a=0,b=1;
	while(i++<n)
	{
		unsigned old_a=a;
		a=b;
		b=old_a+b;
	}
	return a;
}

int main()
{
	printf("��0��fibֵ���ڣ�%d\n",get_fib(0));
	printf("��8��fibֵ���ڣ�%d\n",get_fib(8));
	printf("�ƽ�ָ�������Ƶ��ڣ�%lf\n",get_fib(40)*1.0/get_fib(41));
}