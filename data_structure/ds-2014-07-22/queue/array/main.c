#include <stdio.h>

#define QUEUE_NR 5

enum QUEUE_ACT {DEQ_ACT, ENQ_ACT};

static int queue[QUEUE_NR];
static int enq_ind, deq_ind;
static enum QUEUE_ACT last_act;

static int is_empty(void)
{
	if (enq_ind == deq_ind && last_act == DEQ_ACT) {
		return 1;
	}
	return 0;
}

static int is_full(void)
{
	if (enq_ind == deq_ind && last_act == ENQ_ACT) {
		return 1;
	}
	return 0;
}

int enq(int data)
{
	if (is_full()) {
		return -1;
	}

	queue[enq_ind] = data;
	enq_ind++;
	if (enq_ind == QUEUE_NR) {
		enq_ind = 0;
	}
	last_act = ENQ_ACT;

	return 0;
}

int deq(int *data)
{
	if (is_empty()) {
		return -1;
	}

	*data = queue[deq_ind];
	deq_ind++;
	if (deq_ind == QUEUE_NR) {
		deq_ind = 0;
	}
	last_act = DEQ_ACT;

	return 0;
}

int main(void)
{
	int arr[] = {3,2,1,6,7,8,9,0,};
	int i, j;
	int data;
	int ret;

	for (j = 0; j < 5; j++) {
		for (i = 0; i < 3; i++) {
			ret = enq(arr[i] + j * 3);
			if (ret == -1) {
				printf("stack full, i = %d\n", i);
				break;
			}
		}

		for (i = 0; i < 7; i++) {
			ret = deq(&data);
			if (ret == -1) {
				break;
			}

			printf("%d ", data);
		}
		printf("\n");
	}

	return 0;
}
