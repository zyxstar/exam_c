//�����Ǹ����������Լ��
#include<stdio.h>
unsigned gcd(unsigned a,unsigned b)
{
	while(b)
	{
		unsigned old_a=a;
		a=b;
		b=old_a%b;
	}
	return a;
}

int main()
{
	printf("45��81�����Լ���ǣ�%d\n",gcd(45,81));
	printf("121��77�����Լ���ǣ�%d\n",gcd(121,77));

}