#include <stdio.h>

#define QUEUE_NR 12
enum LAST_ACT {L_DEQ, L_ENQ};

static int queue[QUEUE_NR];
static int enq_ind, deq_ind;
static int last = L_DEQ;

static int is_full(void)
{
	if (enq_ind == deq_ind && last == L_ENQ) {
		return 1;
	}
	return 0;
}

static int is_empty(void)
{
	if (enq_ind == deq_ind && last == L_DEQ) {
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
	last = L_ENQ;

	if (enq_ind == QUEUE_NR) {
		enq_ind = 0;
	}

	return 0;
}

int deq(int *data)
{
	if (is_empty()) {
		return -1;
	}

	*data = queue[deq_ind];
	deq_ind++;
	last = L_DEQ;

	if (deq_ind == QUEUE_NR) {
		deq_ind = 0;
	}

	return 0;
}

int main(void)
{
	int arr[] = {3,2,1,6,7,9,4,8,5};
	int i, j;
	int val;
	int ret;

	for (j = 0; j < 5; j++) {
		for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
			enq(arr[i]);
		}

		//for (i = 0; i < 5; i++) {
		while (1) {
			ret = deq(&val);
			if (ret == -1) {
				break;
			}

			printf("%d ", val);
		}
		printf("\n");
	}

	return 0;
}
