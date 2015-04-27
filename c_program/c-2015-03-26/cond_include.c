//#include <stdio.h>

//#define ARM

//#if defined x86
#ifdef x86
int add(int a, int b)
{
	int c;
	c = a + b;		/*  */
	return c;
}
#elif defined ARM
int add(int aa, int bb)
{
	int cc;
	cc = aa + bb;		/*  */
	return cc;
}
#else
int add(int a, int b)
{
	return a + b;		/*  */
}
#endif

int main(void)
{

}
