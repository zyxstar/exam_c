#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
	int a;
	float b;
	int data[0];
};
int main()
{
	printf("sizeof(struct node)=%d\n",sizeof(struct node));
	struct node *p=malloc(sizeof(struct node)+sizeof(int)*10);
	p->a=100;
	p->b=12.34;
	int i=0;
	for(i=0;i<10;i++)
	{
		p->data[i]=i+100;
	}
	printf("p->a=%d\n",p->a);
	printf("p->b=%f\n",p->b);
	for(i=0;i<10;i++)
	{
		printf("p->data[%d]=%d\n",i,p->data[i]);
	}
	free(p);
	return 0;
}
