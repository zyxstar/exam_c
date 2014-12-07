/* Prim�㷨����С������,����ͼʹ���ڽӾ����ʾ */

#include "Stdio.h"
#include "Conio.h"

#define MaxNum 50          /*ͼ����󶥵���Ϊ50*/
#define MaxEdge 2500       /*ͼ�е�������*/
#define MAX 32767          /*��ʾ��������������,����Ϊ����Ȩֵ����ȡ�������*/

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
G->E[i][j]=MAX;  /*���ڽӾ���Ԫ�ؽ��г�ʼ��*/
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
/*��ͼ�бߵ���Ϣ������һά����edges��*/
typedef struct{       /*����Ԫ�����Ͷ���*/
    char elem1[3];    /*���������ĵ�һ������*/
    char elem2[3];    /*���������ĵڶ�������*/
    int cost;         /*����Ȩֵ*/
   }EdgeType;
EdgeType edges[MaxEdge];
void CreateEdge(MGraph *G,EdgeType edges[])/*������Ϣ���浽һά������*/
{
int i,j;
int k=0;
for(i=0;i<G->n;i++)
   for(j=i;j<G->n;j++)
   if(G->E[i][j]!=MAX)
   {
    strcpy(edges[k].elem1,G->V[i]);
    strcpy(edges[k].elem2,G->V[j]);
    edges[k].cost=G->E[i][j];
    k=k+1;
   }
/*printf("\nk=%d",k);*/
}
void SortEdge(EdgeType edges[],int n)/*��һά�����Ԫ�ذ���cost��С�������ð������*/
{                                    /*n�Ǳ���*/
int i,j;
EdgeType temp;
for (i=n;i>1;i--)
{
    for (j=0;j<i-1;j++)
    if(edges[j].cost>edges[j+1].cost)
    {

      strcpy(temp.elem1,edges[j].elem1);
      strcpy(temp.elem2,edges[j].elem2);
      temp.cost=edges[j].cost;
      strcpy(edges[j].elem1,edges[j+1].elem1);
      strcpy(edges[j].elem2,edges[j+1].elem2);
      edges[j].cost=edges[j+1].cost;
      strcpy(edges[j+1].elem1,temp.elem1);
      strcpy(edges[j+1].elem2,temp.elem2);
      edges[j+1].cost=temp.cost;
    }
}
}
int Find(int father[],int v)
 /*Ѱ�Ҷ���v�������ĸ����,������Ԫ��ֵΪ-1*/
 { int t;
      t=v;
  while(father[t]>=0)
    t=father[t];
  return(t);
 }
void Kruskal(EdgeType edges[],MGraph *G)
 /*��Kruskal����������n�������ͼedges����С������*/
 {
  int father[MaxNum];
  int i,j,v1,v2,vf1,vf2;
  for (i=0;i<G->n;i++) father[i]=-1;
  i=0;j=0;
  printf("\n��С�������ı�Ϊ��\n");
  while(i<G->e && j<(G->n)-1)
    {
      v1=Locate(G,edges[i].elem1);
      v2=Locate(G,edges[i].elem2);
      vf1=Find(father,v1);
      vf2=Find(father,v2);
      if (vf1!=vf2)
       { father[vf2]=vf1;
         j++;  /*j��ʾ��ǰ��С�������Ķ������*/
         printf("(%s,%s) ",edges[i].elem1,edges[i].elem2);
       }
      i++;
    }
}

 struct {
int adjvex;
int lowcost;
}closedge[MaxNum];

void Prim(MGraph *G)
{
/* G Ϊ����洢��ʾ����ͨ����������ķ�㷨�Ӷ��� u ������
���� ��G����С������*/
    int i,j,k;
    int mincost;
    char vex[3];
    printf("\n���빹����С�������Ŀ�ʼ���㣺");
    scanf("%s",vex);
    k = Locate(G, vex);

    printf("\n���ඥ��Ϊ��");
    for(j=0;j<G->n;j++)   /* ���������ʼ��*/
    if (j!=k)
      {
      closedge[j].adjvex = k;
       closedge[j].lowcost=G->E[k][j];
      }
    closedge[k].lowcost = 0;/* ��ʼ״̬��U��{u}*/
    closedge[k].adjvex=k;

    for (i=1; i<G->n; i++)  /* ѡ������ G.vexnum-1 ������*/
    {
        mincost=MAX;
        j=0;k=0;
        while(j<G->n)
        {
        if(closedge[j].lowcost<mincost && closedge[j].lowcost!=0)
        {
            mincost=closedge[j].lowcost;
            k=j;
        }
        j++;
        }
       printf("\n����:%s �ߵ�Ȩֵ:%d",G->V[k],mincost);
       closedge[k].lowcost=0;

       for (j=0;j<G->n;j++)          /*�޸���������ıߵ�Ȩֵ����С�������������*/
      if (G->E[k][j]<closedge[j].lowcost)
      { closedge[j].lowcost=G->E[k][j];
        closedge[j].adjvex=k;/*�� k ���㲢��U��*/
        }
    }
}

main()
{
 /* �˴�������Լ��Ĵ��� */
MGraph mg;
CreateGraph(&mg);
/*CreateEdge(&mg,edges);
SortEdge(edges,mg.e/2);
Kruskal(edges,&mg);*/
Prim(&mg);
getch();
}
