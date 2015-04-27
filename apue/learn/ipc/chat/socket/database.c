#include <stdlib.h>

#include <protocol.h>
#include <llist.h>
#include <database.h>

struct database_st {
	LLIST *llist;
	llist_cmp *cmp_id;
};

void *server_online_db;

static int key_id_cmp(const void *key, const void *data)
{
	const uint32_t *k = key;
	const struct database_record_st *d = data;

	return *k - d->id;
}

int database_init(void)
{
	struct database_st *db;

	db = malloc(sizeof(*db));
	if (db == NULL) {
		goto malloc_db_err;
	}

	db->llist = llist_creat(sizeof(struct database_record_st));
	if (db->llist == NULL) {
		goto llist_creat_err;
	}

	db->cmp_id = key_id_cmp;
	server_online_db = db;

	return 0;


	free(db->llist);
llist_creat_err:
	free(db);
malloc_db_err:
	return -1;
}

void database_destroy(void)
{
	struct database_st *db = server_online_db;

	llist_destroy(db->llist);
	free(db);
}

int database_insert(const struct database_record_st *record)
{
	struct database_st *db = server_online_db;

	return llist_insert(db->llist, record, DIR_BACK);
}

struct database_record_st *database_find(uint32_t id)
{
	struct database_st *db = server_online_db;

	return llist_search(db->llist, &id, db->cmp_id);
}

void database_update(uint32_t id)
{
	struct database_st *db = server_online_db;
	struct database_record_st *record;

	record = llist_search(db->llist, &id, db->cmp_id);
	if (record == NULL) {
		return;
	}

	record->last = time(NULL);
}

struct getlist_st {
	uint32_t *list;
	int ind;
	int num;
};

static void getlist_op(void *record, void *arg)
{
	struct getlist_st *gl = arg;
	struct database_record_st *rcd = record;
	time_t cur;

	cur = time(NULL);
	if (rcd->online == 0 || cur - rcd->last > OFFLINE_INTERVAL) {
		return;
	}

	if (gl->ind == gl->num) {
		return;
	}

	gl->list[gl->ind++] = rcd->id;
}

int database_getlist(uint32_t list[], int num)
{
	struct getlist_st gl = {list, 0, num};
	struct database_st *db = server_online_db;

	llist_travel(db->llist, getlist_op, &gl);

	return gl.ind;
}
