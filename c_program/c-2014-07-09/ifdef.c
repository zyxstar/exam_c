//#define X86 32167

//#if defined X86
#ifdef X86
int add(int a, int b)
{
	return a + b;
	X86;
}
#elif defined ARM
int add(int a, int b, int c)
{
	return a + b + c;
}
#endif
