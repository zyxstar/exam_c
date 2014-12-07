/* ���������������ͼ��ͼ���ڽӾ���洢*/
#include "Stdio.h"
#include "Conio.h"

#define MaxNum 50        /*ͼ����󶥵�����Ϊ50*/
int visited[MaxNum];

    typedef char VexType[3];           /*ͼ�Ķ���������Ϊ�ַ����飬2���ַ�����*/
    typedef int EdgeType;              /*�����ߣ���Ȩֵ��Ϊ����*/
    typedef struct {
       VexType V[MaxNum]; /*һά����洢������Ϣ*/
       EdgeType E[MaxNum][MaxNum]; /*��ά�����ʾ�ڽӾ��󣬴洢�ߵ���Ϣ*/
       int n,e;                       /*�������ͱ���*/
      }MGraph;                      /*ͼ���Ͷ���*/

int Locate(MGraph *G,char vex[])  /*ȷ��������ͼG�е�λ�ã�����G->V�е����*/
{
int i;
for(i=0;i<G->n;i++)
if(strcmp(G->V[i],vex)==0)
return i;
}

typedef struct
{
int data[MaxNum];
int front,rear;
} Queue;

void InitQueue(Queue *q)
{
q->front=q->rear=-1;
}

void InQueue(Queue *q,int x)
{
    if ((q->rear+1)==MaxNum)
        printf("Overflow");
    else
    {
        q->rear++;
        q->data[q->rear]=x;
    }
}

int OutQueue(Queue *q)
{
    if(q->front==q->rear)
        return(NULL);
    else
    {
        q->front++;
        return(q->data[q->front]);
    }
}

int EmptyQueue(Queue *q)
{
    if(q->rear==q->front)
        return(1);
    else
        return(0);
}

void CreateGraph(MGraph *G)
      {
       int i,j,k;
       char vex1[3],vex2[3];/*��������Ķ���*/
       printf("\n����ͼ�Ķ������ͱ���(�ö��ŷָ�):");
       scanf("%d,%d",&(G->n),&(G->e));/*���붥�����ͱ���*/
       printf("����ͼ�Ķ�����Ϣ(�2���ַ�):");
for (i=0;i<G->n;i++)
{
 scanf("\n%s",G->V[i]); /*����n������ı�ʶ��Ϣ��������������*/
}
       for (i=0;i<G->n;i++)
   for (j=0;j<G->n;j++)  
G->E[i][j]=0;  /*���ڽӾ���Ԫ�ؽ��г�ʼ��*/
       printf("\n����ͼ��ÿ��������������������ı�ʶ��Ϣ:");
       for (k=0;k<G->e;k++)         /*����e����*/
        {
        printf("\n�����%d���ߵĵ�1�����㣺",k+1);
        scanf("%s",vex1);
        printf("�����%d���ߵĵ�2�����㣺",k+1);
        scanf("%s",vex2);

        i=Locate(G,vex1);j=Locate(G,vex2);
   /*     scanf("\n%d,%d",&i,&j); */   /*����ÿ�����������Ķ����ڶ�ά�����е��±꣬�����ڽӾ���*/
         G->E[i][j]=1;             /*���ͬʱ����G->E[j][i]=1;�����ǽ�������ͼ���ڽӾ���*/
        }
}
void PrintGraph(MGraph *G)/*��ӡͼ�Ķ���ͱߵ���Ϣ*/
{
int i,j;
printf("\nͼ�ж������Ϊ��%d",G->n);
printf("\nͼ�б���Ϊ��%d",G->e);
printf("\nͼ�ж���Ϊ��");
for (i=0;i<G->n;i++)
printf("%c%c ",G->V[i][0],G->V[i][1]);
printf("\nͼ�б�Ϊ��");
for(i=0;i<G->n;i++)
   for(j=0;j<G->n;j++)
    if(G->E[i][j])
        printf("[%c%c,%c%c] ",G->V[i][0], G->V[i][1], G->V[j][0], G->V[j][1]);
}

      void BFSMG(MGraph *G,int k)
      {/*�Ӷ���Vi�����������ڽӾ���洢��ͼG���й��������������BFS*/
       int i,j;
       Queue Q;                        /*��������Q*/
       InitQueue(&Q);                  /*��ʼ������Q*/
       printf("���ʶ���:%s\n",G->V[k]);   /*���ʶ���Vk*/
       visited[k]=1;
       InQueue(&Q,k);                 /*����Vk�����*/
       while (!EmptyQueue(&Q))
         {i=OutQueue(&Q);                 /*����Vi������*/
          for (j=0;j<G->n;j++)               /*��������Vi���ڽӵ�Vj*/
          if (G->E[i][j]==1 && !visited[j])     /*��Vjδ����*/
           {printf("���ʶ���:%s\n",G->V[j]);  /*����Vj */
             visited[j]=1;
               InQueue(&Q,j);                  /*���ʹ���Vj�����*/
           }
         }
      }
void BFSTraMG(MGraph *G)
      {/*������ȱ���ͼG����ͼ�����ڽӾ���洢��*/
       int i;
       for (i=0;i<G->n;i++)
         visited[i]=0;              /*��ʼ�����ʱ�־����*/
       for (i=0;i<G->n;i++)
         if (!visited[i]) BFSMG(G,i);    /*����ǰ����viδ�����ʹ������vi��ʼ���й�����ȱ���BFS*/
      }




main()
{
 /* �˴�������Լ��Ĵ��� */
 MGraph mg;
 CreateGraph(&mg);
 /*PrintGraph(&alg);*/
 printf("������ȱ�������ͼ��\n");
 BFSTraMG(&mg);

}
