#include <unistd.h>

#include <stdio.h>

void display0(int step)
{
	if (step == 0) {
		return;
	}
	if (step % 5 == 0) {
		printf("#");
		fflush(NULL);
	}
}

void display1(int step)
{
	int c_nr, blank_nr;
	int i;

	c_nr = step / 5;
	blank_nr = 20 - c_nr;

	printf("\r[");

	i = 0;
	while (i < c_nr) {
		printf("#");
		i++;
	}
	i = 0;
	while (i < blank_nr) {
		printf(" ");
                i++;
	}
	printf("]%d%%", step);
	fflush(NULL);
}

int main(void)
{
	int step;

	step = 0;
	while (step <= 100) {
		display1(step);
		step++;
		usleep(200000);
	}
	printf("\n");

	return 0;
}
