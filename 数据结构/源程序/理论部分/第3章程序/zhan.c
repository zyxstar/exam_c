/*  HELLO.C -- Hello, world */

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"
#define MAXSIZE 10


typedef  struct     { 
    int data[MAXSIZE];  /*���ݵĴ洢��*/
    int front,rear;  /*��ͷ��βָ��*/
  }c_SeQueue;    /*ѭ����*/



c_SeQueue*  Init_SeQueue()  /*����һ����ͷ���Ŀն�*/
 {
  c_SeQueue *q;
  q=malloc(sizeof(c_SeQueue));
  q->front=q->rear=0;
  return q;
 }

int In_SeQueue(c_SeQueue *q ,int x) /*�����*/
{
         if ( (q->rear+1) % MAXSIZE==q->front)
        {
          printf("����");
          return -1;   /*�����������*/
        }
        else
        {
         q->rear=(q->rear+1) % MAXSIZE;
         q->data[q->rear]=x;
         return 1;    /*������*/
        }
}


int Out_SeQueue(c_SeQueue *q ,int *x) /*������*/
{
      if(q->rear==q->front)
      {
        printf("�ӿ�");
        return -1;   /*�ӿղ��ܳ���*/
      }
     else
      {
       q->front=(q->front+1)%MAXSIZE;
       *x=q->data[q->front]; /*������ͷԪ��*/
       return 1;    /*�������*/
       }
}


int Empty_SeQueue(c_SeQueue  *q)    /*�жӿ�*/
{  
  if  (q->rear == q->front)  return 1;
       else return 0;
}

int Full_SeQueue(c_SeQueue  *q)    /*�жӿ�*/
{  
  if  ((q->rear+1) % MAXSIZE== q->front)  return 1;
  else return 0;
}

main()
{
    c_SeQueue *cq;
    int select,i;
    int y,*z;
    cq=Init_SeQueue();

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
               In_SeQueue(cq ,y);

               break;
        case 2:Out_SeQueue(cq,z);
               printf("the elements are:\n ");
               for(i=cq->front+1;i!=(cq->rear+1)%MAXSIZE;i=(i+1)%MAXSIZE)
                 printf("%d ",cq->data[i]);
               break;
      }
    printf("\n(1)Input a stack data");
    printf("\n(2)Onput a stack data");
    printf("\n(3)Exit");
    printf("\nPlease select one=>");
    scanf("%d",&select);
    printf("\n");
   }
    while(select!=3);
}
