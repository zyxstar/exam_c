#include<stdio.h>
#include<stdlib.h>
//����[0,1)��ľ��ȷֲ�С��
double rand01()
{
	return rand()/32768.0;
}

//mu����ѧ������omg�Ƿ���
double normal(double mu,double omg)
{
	double sum=0.0;
	int i;
	for(i=0;i<12;i++)
		sum+=rand01();
	sum-=6.0;
	return sum*omg+mu;
}

//���ԣ�����200000����ѧ����Ϊ10.0,����Ϊ����ֵ����������ֱ�ͳ�Ƹ���������������ֵĴ���
void test(double omg)
{
	int arr[21]={0},i,index;
	for(i=0;i<200000;++i)
	{
		index=(int)(normal(10.0,omg)+0.5);
		if(index<0) index=0;
		if(index>20) index=20;
		arr[index]++;
	}
	for(i=0;i<21;++i)
		printf("%d������С�����֣�%d��\n",i,arr[i]);
}
int main()
{
	test(0.1);
	printf("\n");
	test(1);
	printf("\n");
	test(5);
	printf("\n");

	
	return 0;
}