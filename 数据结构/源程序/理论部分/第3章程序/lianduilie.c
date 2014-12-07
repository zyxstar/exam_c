/*  HELLO.C -- Hello, world */

#include "stdio.h"
#include "stdlib.h"
#define MAXSIZE 10


typedef struct node
 { int  data;
   struct  node *next;
 } QNode;     /*���ӽ�������*/
typedef struct 
 { QNode   *front,*rear;
 }LQueue;     /*��ͷβָ���װ��һ�������*/


LQueue  *Init_LQueue()
{
  LQueue *q;
  QNode *p;
  q=malloc(sizeof(LQueue)); /*����ͷβָ����*/
  p=malloc(sizeof(QNode));  /*��������ͷ���*/
  p->next=NULL;
  q->front=q->rear=p;
  return q;
}


void In_LQueue(LQueue *q , int  x)
{  QNode *p;
   p=malloc(sizeof(QNode));  /*�����½��*/
   p->data=x;   p->next=NULL;
   q->rear->next=p;
   q->rear=p;
}


int  Empty_LQueue( LQueue *q)
{
   if (q->front==q->rear)   return 0;
   else  return 1;
}


int Out_LQueue(LQueue *q , int  *x)
{  QNode *p;
   if (Empty_LQueue(q) )
    {
      printf ("�ӿ�"); return 0;
    }   /*�ӿգ�����ʧ��*/
   else
         { p=q->front->next;
           q->front->next=p->next;
           *x=p->data;/*��ͷԪ�ط�x��*/
           free(p);
           if (q->front->next==NULL)
           q->rear=q->front;  
                /*ֻ��һ��Ԫ��ʱ�����Ӻ�ӿգ���ʱ��ҪҪ�޸Ķ�βָ��ο�ͼ3.16(c)*/
           return 1;
         }
}


main()
{
    LQueue  *lq;
    int select,i;
    int y,*z;
    lq=Init_LQueue();

    printf("\n(1)Input a stack data");
    printf("\n(2)Onput a stack data");
    printf("\n(3)Exit");
    printf("\nPlease select one=>");
    scanf("%d",&select);
    do
    {
      switch(select)
      {
        case 1:printf("\nPlease input the data=>");
               scanf("%d",&y);
               In_LQueue(lq,y);
               break;
        case 2:Out_LQueue(lq,z);
               printf("the elements are:\n ");
               break;
      }
    printf("\n(1)Input  data");
    printf("\n(2)Onput  data");
    printf("\n(3)Exit");
    printf("\nPlease select one=>");
    scanf("%d",&select);
    printf("\n");
   }
    while(select!=3);
}
