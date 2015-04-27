#include <stdio.h>

#include <linux/input.h>

/* ./a.out path */
int main(int argc, char **argv)
{
	FILE *fp;
	struct input_event event;

	if (argc != 2) {
		printf("argment...\n");
		return 1;
	}

	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("open %s failed.\n", argv[1]);
		return 1;
	}

	while (1) {
		fread(&event, sizeof(event), 1, fp);
		switch (event.type) {
		case EV_KEY:
			if (event.code == BTN_LEFT) {
				if (event.value == 1) {
					printf("left down\n");
				} else {
					printf("left up\n");
				}
			} else if (event.code == BTN_RIGHT) {
				if (event.value == 1) {
                                        printf("right down\n");
                                } else {
                                        printf("right up\n");
                                }
			} else if (event.code == BTN_MIDDLE) {
				if (event.value == 1) {
                                        printf("middle down\n");
                                } else {
                                        printf("middle up\n");
                                }
			}
			break;
		case EV_REL:
			if (event.code == REL_X) {
				printf("x: %d\n", event.value);
                        } else if (event.code == REL_Y) {
				printf("y: %d\n", event.value);
                        }
			break;
		case EV_SYN:
			printf("-------------------\n");
			break;
		}
	}

	fclose(fp);

	return 0;
}
