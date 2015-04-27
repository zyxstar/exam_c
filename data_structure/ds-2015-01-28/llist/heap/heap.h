#ifndef HS_HEAP_H
#define HS_HEAP_H

void *hsheap_init(void *ptr, int size);

void hsheap_destroy(void *);

void *hsheap_alloc(void *handle, int size);

void hsheap_free(void *handle, void *ptr);

#endif	/* HS_HEAP_H */
