#ifndef _CHART_H__
#define _CHART_H__

#define SORTUP 1
#define SORTDN 2

struct chart_node;
typedef int chart_t;
typedef struct chart_node *CHART;

CHART chart_create(int capacity);
int chart_is_empty(CHART head);
int chart_is_full(CHART head);
void chart_make_empty(CHART head);
int chart_sort(CHART head, int mode);
int chart_insert_tail(CHART head, const chart_t *data);
int chart_insert(CHART head, int pos, const chart_t *data);
int chart_delete(CHART head, int pos);
void *chart_find_value(CHART head, int pos);
int chart_find_pos(CHART head, const chart_t *data);
void chart_display(CHART head);
void chart_dispose(CHART head);

struct chart_node {
	chart_t *data;
	int size;
	int capacity;
};

#endif
