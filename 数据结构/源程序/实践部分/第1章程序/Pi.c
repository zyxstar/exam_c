//�����ʽ4-4/3+4/5-4/7......��ǰn��֮��
#include<stdio.h>
double get_pi(unsigned n)
{
	double res=0;
	unsigned i;
	for(i=1;i<=n;i++)
		if(i%2)
			res+=4.0/(2*i-1);
		else
			res-=4.0/(2*i-1);
	return res;
}

int main()
{
	printf("pi���Ƶ��ڣ�%lf\n",get_pi(10000000));
	return 0;
}
