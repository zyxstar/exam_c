#include <stdio.h>

#include "heap.h"

#define MEM_BUF_SIZE 2048

static char mem_buf[MEM_BUF_SIZE];

int main(void)
{
	void *handle;
	void *p[4];
	int i;

	printf("start: %p, end: %p\n", mem_buf, mem_buf + MEM_BUF_SIZE);

	handle = hsheap_init(mem_buf, MEM_BUF_SIZE);

	for (i = 0; i < 4; i++) {
		p[i] = hsheap_alloc(handle, 256);
		printf("p[%d] = %p\n", i, p[i]);
	}

	hsheap_free(handle, p[1]);
	hsheap_free(handle, p[0]);
	p[1] = hsheap_alloc(handle, 512);
	printf("p[1] = %p\n", p[1]);

	hsheap_destroy(handle);

	return 0;
}
