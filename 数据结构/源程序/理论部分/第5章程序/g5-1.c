/*ͼ���ڽӾ����ʾ*/

#include "Stdio.h"
#include "Conio.h"
#include"stdio.h"
       #define MaxNum 50        /*ͼ����󶥵�����Ϊ50*/
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

void CreateGraph(MGraph *G)
      {
       int i,j,k;
       char vex1[3],vex2[3];/*��������Ķ���*/
       printf("\n����ͼ�Ķ������ͱ���(�ö��ŷָ�):");
       scanf("%d,%d",&(G->n),&(G->e));/*���붥�����ͱ���*/
       printf("����ͼ�Ķ�����Ϣ(�2���ַ�):");
for (i=0;i<G->n;i++)
{
 /*G->V[i][0]=G->V[i][1]=0;*/
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
        /* scanf("%s\n%s",vex1,vex2);*/
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


main()
{
MGraph mg;

CreateGraph(&mg);
PrintGraph(&mg);

/*printf("ͼ�ж������Ϊ��%d,ͼ�б���Ϊ��%d",mg.n,mg.e);
printf("\nͼ�ж���Ϊ��");
for (i=0;i<mg.n;i++)
printf("%c%c ",mg.V[i][0],mg.V[i][1]); ����n������ı�ʶ��Ϣ��������������
printf("\nͼ�б�Ϊ��");
for(i=0;i<mg.n;i++)
   for(j=0;j<mg.n;j++)
    if(mg.E[i][j])
        printf("[%c%c,%c%c] ",mg.V[i][0],mg.V[i][1],mg.V[j][0],mg.V[j][1]);*/

getch();
}
