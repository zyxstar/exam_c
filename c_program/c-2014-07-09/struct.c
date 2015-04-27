#include <stdio.h>

struct coop {
	int x, y, z;
};

struct cs {
	int life;
	int attack;
	int defense;
	int speed;
	struct coop coop;
	struct cs *p;
};

void foo(const struct cs *xxx)
{

}

int main(void)
{
	struct cs a = {11,22,33,};
	struct cs b;
	struct cs *p = &b;

	b = a;
	foo(&a);

	(*p).life;
	p->life;

	printf("%d %d %d %d\n", a.life, a.attack, a.defense, a.speed);

	a.life -= 10;

	printf("%d %d %d %d\n", a.life, a.attack, a.defense, a.speed);

	return 0;
}
