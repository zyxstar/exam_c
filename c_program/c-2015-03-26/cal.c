#include <stdio.h>

int push(int);
int pop(void);

int main(void)
{
	char str[] = "352*+63/-";
	int i;
	int val;

	for (i = 0; str[i] != '\0'; i++) {
		switch (str[i]) {
		case '0': case '1': case '2':
		case '3': case '4': case '5':
		case '6': case '7': case '8':
		case '9':
			push(str[i] - '0');
			break;
		case '+':
			push(pop() + pop());
			break;
		case '-':
			val = pop();
			push(pop() - val);
			break;
		case '*':
			push(pop() * pop());
			break;
		case '/':
			val = pop();
			push(pop() / val);
			break;
		}
	}

	printf("%s = %d\n", str, pop());

	return 0;
}
