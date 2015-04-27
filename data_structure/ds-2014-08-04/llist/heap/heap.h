#ifndef HS_HEAP_H
#define HS_HEAP_H

typedef void HEAP;

HEAP *heap_init(void *ptr, int size);

void heap_destroy(HEAP *);

void *heap_alloc(HEAP *, int size);

void heap_free(HEAP *, void *ptr);

#endif	/* HS_HEAP_H */
