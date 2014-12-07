/*�Ͻ�˹�����㷨��������ʹ���ڽӾ���洢 */

#include "Stdio.h"
#include "Conio.h"

#define MaxNum 50          /*ͼ����󶥵���Ϊ50*/
#define MAX 32767          /*��ʾ��������������,����Ϊ����Ȩֵ����ȡ�������*/
#define TRUE 1
#define FALSE 0

typedef char VexType[3];        /*ͼ�Ķ���������Ϊ�ַ����飬2���ַ�����*/
typedef struct {
    VexType V[MaxNum];          /*һά����洢������Ϣ*/
    int E[MaxNum][MaxNum]; /*��ά�����ʾ�ڽӾ��󣬴洢�ߵ���Ϣ*/
    int n,e;                    /*�������ͱ���*/
}MGraph;                        /*ͼ���Ͷ���*/

int Locate(MGraph *G,char vex[])  /*ȷ��������ͼG�е�λ�ã�����G->V�е����*/
{
int i;
for(i=0;i<G->n;i++)
if(strcmp(G->V[i],vex)==0)
return i;
}

void CreateGraph(MGraph *G)
      {
       int i,j,k,cost;
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
   {if(j==i)  G->E[i][j]=0;
    else G->E[i][j]=MAX;  /*���ڽӾ���Ԫ�ؽ��г�ʼ��*/
   }
       printf("\n����ͼ��ÿ��������������������ı�ʶ��Ϣ:");
       for (k=0;k<G->e;k++)         /*����e����*/
        {
        printf("\n�����%d���ߵĵ�1�����㣺",k+1);
        scanf("%s",vex1);
        printf("�����%d���ߵĵ�2�����㣺",k+1);
        scanf("%s",vex2);
        /* scanf("%s\n%s",vex1,vex2);*/
        i=Locate(G,vex1);j=Locate(G,vex2);
   /*     scanf("\n%d,%d",&i,&j); */   /*����ÿ�����������Ķ����ڶ�ά�����е��±꣬�����ڽӾ���*/
        printf("�����%d���ߵ�Ȩֵ��",k+1);
        scanf("%d",&cost);
         G->E[i][j]=cost;             /*���ͬʱ����G->E[j][i]=cost;�����ǽ�������ͼ���ڽӾ���*/
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


void Dijkstra(MGraph *G)
    { /*��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����·������D[v]

    v0ΪԴ����һά�����е���ţ�p[n][n]Ϊ��ά���飬��v����Ϊ1��Ԫ�ر�ʾ�˴�Դ�㵽v�����·�����������Ķ��㡣
      ��P[v][w]ΪTRUE����w�Ǵ�v0�� v��ǰ������·���ϵĶ���*/
      /*final[v] ΪTRUE���ҽ���v��S, �����Ѿ���ô�v0��v�����·��*/

   int final[MaxNum];/*ΪTRUE��ʾ��ʾ��Ԫ���������·�����յ㼯��S��ΪFALSE��ʾ������*/
   int P[MaxNum][MaxNum];/*P[w][v]ΪTRUE����ʾ��Դ�㵽����w�����·����������v*/
   int D[MaxNum];/*Դ�㵽����v��·������D[v]*/
   int v0,v,w;/*������ű���,v0ΪԴ��*/
   int i,j,min; /*i,j��ѭ��������min���浱ǰ��·����Сֵ*/
   char vex[3];

   printf("\n����Դ�㣺");
   scanf("%s",vex);
   v0=Locate(G,vex);

   for (v=0;v<G->n;v++)
   {
    final[v]=FALSE; /*S���ϳ�ʼΪ��*/
    D[v]=G->E[v0][v];/*Դ�㵽���յ�����·���ĳ�ֵ*/

    for (w=0; w<G->n;w++)  P[v][w]=FALSE;  /*���·��*/

    if(D[v]<MAX) {P[v][v0]=TRUE; }/*��v0��v�ĵ�ǰ�����·��*/
    }

    D[v0]=0; final[v0]=TRUE;        /*��ʼ����v0��������S��*/

    /*��ʼ��ѭ����ÿ�����v0��ĳ��v ��������·��������v��S��*/
      for(i=1; i<G->n; i++)          /*����n-1������*/
      {
      min=MAX;                       /*minΪ��ǰ��֪��v0������������*/
      for (w=0;w<G->n;w++)
        if (!final[w])               /*w������V��S��*/
            if (D[w]<min)
             {v=w; min=D[w];}        /*v�������·�����յ�����*/

      final[v]=TRUE;                 /*��v0���������v����S����*/

      for(w=0;w<G->n;w++)                      /*���µ�ǰ���·��*/
         if(!final[w]&&(min+G->E[v][w]<D[w])&&(G->E[v][w]!=MAX))  /*�޸�D[w]��P[w],w��V-S*/
            {
             D[w]=min+G->E[v][w];

             for(j=0;j<G->n;j++)
                P[w][j]=P[v][j];     /*P[w]=P[v]; */
             P[w][v]=TRUE;              /*Դ�㵽w�����·����Դ�㵽v�����·������v��w�Ļ���*/
            }
      }

for(w=0;w<G->n;w++)
{
if(w!=v0)
{
printf("\nԴ��%s���յ�%s�����·������Ϊ��%d\n",G->V[v0],G->V[w],D[w]);

printf("�����Ķ���Ϊ��");
printf("%s  ",G->V[v0]);
for(v=0;v<G->n;v++)
    if(v!=v0 && P[w][v])
        printf("%s  ",G->V[v]);
printf("%s  ",G->V[w]);

}

}

}


main()
{
 /* �˴�������Լ��Ĵ��� */
 MGraph mg;
 CreateGraph(&mg);
 Dijkstra(&mg);

getch();
}
