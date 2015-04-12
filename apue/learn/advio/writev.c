#include <sys/uio.h>

int main(void)
{
	char hello[] = "hello ";
	char world[] = "world\n";
	struct iovec vec[2] = {
		{hello, sizeof(hello)},
		{world, sizeof(world)},
	};

	writev(1, vec, 2);

	return 0;
}
