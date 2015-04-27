#include <stdio.h>

int cal(char str[])
{
	int i;
	int ret;

	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			push(str[i] - '0');
		} else if (str[i] == '+') {
			push(pop() + pop());
		} else if (str[i] == '-') {
			ret = pop();
			push(pop() - ret);
		} else if (str[i] == '*') {
			push(pop() * pop());
		} else if (str[i] == '/') {
			ret = pop();
			push(pop() / ret);
		}
	}

	return pop();
}

int main(void)
{
	char str[] = "532*+84/-";
	int val;

	val = cal(str);
	printf("val = %d\n", val);

	return 0;
}
