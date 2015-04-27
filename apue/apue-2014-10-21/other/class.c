
struct animal {
	int family;
	char data[0];
};

struct beast {
	int family;
	int teeth;
};

struct bird {
	int family;
	int cb;
	int ym;
};

foo(struct animal *obj)
{
	struct beast *b;
	struct bird *bb;

	switch (obj->family) {
	case BIRD:
		bb = ()obj;
		bb->ym;
		break;
	case BEAST:
		break;
	}
}
