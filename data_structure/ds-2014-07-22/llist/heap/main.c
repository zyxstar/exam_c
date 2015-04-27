#include <stdio.h>

#include "heap.h"

static char membuf[4096];

int main(void)
{
	HEAP *handle;
	int *p;

	handle = heap_init(membuf, 4096);

	p = heap_alloc(handle, sizeof(*p));
	/* if error */

	*p = 123;

	heap_free(handle, p);

	heap_destroy(handle);

	return 0;
}
