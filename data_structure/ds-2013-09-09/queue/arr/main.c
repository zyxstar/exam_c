#include <stdio.h>

#define QUEUE_NR 6

enum LAST_SEQ {L_DEQ, L_ENQ};

static int queue[QUEUE_NR];
static int enq_ind, deq_ind;
static enum LAST_SEQ seq = L_DEQ;

static int is_empty(void)
{
	if (enq_ind == deq_ind && seq == L_DEQ) {
		return 1;
	}
	return 0;
}

static int is_full(void)
{
	if (enq_ind == deq_ind && seq == L_ENQ) {
		return 1;
	}
	return 0;
}

int enq(int data)
{
	if (is_full()) {
		return -1;
	}

	queue[enq_ind % QUEUE_NR] = data;
	enq_ind++;
	if (enq_ind >= QUEUE_NR) {
		enq_ind = 0;
	}
	seq = L_ENQ;
	return 0;
}

int deq(int *data)
{
	if (is_empty()) {
		return -1;
	}

	*data = queue[deq_ind];
	deq_ind++;
	if (deq_ind >= QUEUE_NR) {
		deq_ind = 0;
	}
	seq = L_DEQ;
	return 0;
}

int main(void)
{
	int arr[] = {11,22,33,44,55,66,77,88};
	int i, j;
	int data;
	int ret;

	for (j = 0; j < 4; j++) {
		for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
			ret = enq(arr[i]);
			if (ret == -1) {
				printf("queue is full.\n");
				break;
			}
		}

		for (i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
			ret = deq(&data);
			if (ret == -1) {
				printf("queue is empty.\n");
				break;
			}
			printf("%d ", data);
		}
		printf("\n");
	}

	return 0;
}
