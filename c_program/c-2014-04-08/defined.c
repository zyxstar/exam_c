//#define ARM

//#if defined X86
#ifdef X86
int add(int a, int b)
{
	int c = XXX;
	return a + b;
}
#elif defined ARM
int add(int a, int b)
{
	int arm;
	arm = a + b;
	return arm;
}
#endif
