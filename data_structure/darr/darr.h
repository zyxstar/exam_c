#ifndef _DARR_H__
#define _DARR_H__

typedef void darr_print(const void *);
typedef int darr_cmp(const void *data, const void *key);
// 0:相同 !0:不相同

struct darr_node;
typedef struct darr_node *DARR;

DARR darr_create(int size);
int darr_insert(DARR head, const void *data);
void *darr_find(DARR head, const void *key, darr_cmp *fun);
int darr_find_all(DARR head, const void *key, darr_cmp *fun, void ***find_data);
int darr_delete(DARR head, const void *key, darr_cmp *fun);
void darr_display(DARR head, darr_print *fun);
void darr_dispose(DARR head);

struct darr_node {
	char *data; // 存储任意类型数据
	int each; // 每一个数据占多少字节
	int size; // 已经存储多少个
};

#endif
