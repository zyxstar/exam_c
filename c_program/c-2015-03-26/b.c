static int abc;

static void foo(void)
{
	static int a = 0;
	a++;
}

void *xxx(void)
{
	bar(foo);
}
