#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

#include <linux/input.h>

#if 0
struct input_event {
        struct timeval time;
        __u16 type;
        __u16 code;
        __s32 value;
};
#endif

/* # ./a.out /dev/input/eventX */
int main(int argc, char **argv)
{
	int fd;
	struct input_event event;

	/* if argment... */

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror(argv[1]);
		return 1;
	}

	while (1) {
		read(fd, &event, sizeof(event));
		/* if error */

		printf("type: %d, code: %d, value: %d\n", event.type, event.code, event.value);
	}

	close(fd);

	return 0;
}
