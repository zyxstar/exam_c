#include <my_global.h>
#include <my_sys.h>
#include <mysql.h>

#include <stdio.h>

int main(int argc, char **argv)
{
	MYSQL *handle;
	MYSQL *retp;

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

	mysql_close(handle);
	mysql_library_end();

	return 0;


mysql_real_connect_err:
	mysql_close(handle);
mysql_init_err:
	return 1;
}
