#include <stdio.h>
#include <math.h>
int fun(int n)
{
	int sum=0;
	int i=0;
	for(i=0;i<n;i++)
	{
		sum=sum+i;
	}
	return sum;
}
int main()
{
	int j=0;
	int n=0;
	int m=fun(20);
	for(j=0;j<10;j++)
	{
		n=n+j;
	}
	printf("n=%d\n",n);
	printf("m=%d\n",m);
	return 0;
}
