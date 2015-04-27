#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

#include <stdio.h>

static void print_result(MYSQL_RES *res)
{
	int i;
	MYSQL_ROW row;

	while (1) {
		row = mysql_fetch_row(res);
		if (row == NULL) {
			break;
		}

		for (i = 0; i < mysql_num_fields(res); i++) {
			printf("%s ", row[i]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv)
{
	MYSQL *handle;
	MYSQL *retp;
	int ret;
	MYSQL_RES *res;

	MY_INIT(argv[0]);

	mysql_library_init(0, NULL, NULL);

	handle = mysql_init(NULL);
	if (handle == NULL) {
		fprintf(stderr, "mysql_init() failed\n");
		goto mysql_init_err;
	}

	retp = mysql_real_connect(handle, NULL, "root", "123", NULL, 0, NULL, 0);
	if (retp == NULL) {
		fprintf(stderr, "%s\n", mysql_error(handle));
		goto mysql_real_connect_err;
	}

	ret = mysql_query(handle, "select * from apue.t1 where sex='male';");
	if (ret) {
		fprintf(stderr, "%s\n", mysql_error(handle));
	}

	res = mysql_store_result(handle);
	if (res == NULL) {
		fprintf(stderr, "%s\n", mysql_error(handle));
	} else {
		print_result(res);
	}

	mysql_free_result(res);

	mysql_close(handle);
	mysql_library_end();

	return 0;


mysql_real_connect_err:
	mysql_close(handle);
mysql_init_err:
	return 1;
}
