#include <stdio.h>

/* O * 4 + O7 = 29 */
int main(void)
{
	int i, j;

	for (i = 0; i <= 9; i++) {
		if (i == 4 || i == 7 || i == 2 || i == 9) {
			continue;
		}
		for (j = 0; j <= 9; j++) {
			if (j == 4 || j == 7 || j == 2 || j == 9) {
				continue;
			}
			if (i == j) {
				continue;
			}

			if (i * 4 + j * 10 + 7 == 29) {
				printf("%d * 4 + %d7 = 29\n", i, j);
			}
		}
	}

	return 0;
}
