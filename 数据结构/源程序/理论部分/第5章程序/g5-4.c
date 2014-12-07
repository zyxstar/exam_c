/* ����ͼ���ڽӶ��������ʾ*/

#include "Stdio.h"
#include "Conio.h"
#define MaxNum 50
    typedef struct EdgeNode{     /*����߽�����ͣ����費���Ǳߵķ��ʱ�Ǻͱ��ϵ�Ȩֵ�������ص���Ϣ*/
    int ivex,jvex;                /*�ñ������������������λ��*/
    struct EdgeNode *ilink, *jlink;  /*ָ���򣬷ֱ�ָ�������������������һ����*/
    } EdgeNode ;
    typedef struct VexNode{  /*���嶥��������*/
    char vertex[3];          /*����ֵ������Ϊ�ַ����飬2���ַ�����*/
    EdgeNode *firstedge;    /*ָ���һ�������ö���ı�*/
    } VexNode ;
    typedef struct{          /*�����������洢��ͼ����*/
    VexNode adjmulist[MaxNum];
    int vexnum,edgenum;     /*����ͼ�еĶ������ͱ���*/
}AMLGraph;

int Locate(AMLGraph *G,char vex[])  /*ȷ��������ͼG�е�λ�ã�����G->V�е����*/
{
int i;
for(i=0;i<G->vexnum;i++)
if(strcmp(G->adjmulist[i].vertex,vex)==0)
return i;
}

void CreateAMLG(AMLGraph *G) /*���ö��������ʾ����������ͼG*/
{
int i,j,k;
char vex1[3],vex2[3];
EdgeNode * s;
printf("��������ͼ�Ķ������ͱ������ö��ŷָ�����\n");
scanf ("%d,%d",&(G->vexnum),&(G->edgenum)); 
printf("���붥����Ϣ(������2���ַ�)��\n");
for (i=0;i<G->vexnum;i++)             /*���������*/
{ 
scanf("\n%s",G->adjmulist[i].vertex);    /*����ÿ������ı�ʶ��Ϣ*/
G-> adjmulist[i].firstedge=NULL;         /*��ʼ��ָ��*/
}
for(k=0;k<G->edgenum; k++)                    /*����e���ߣ������������*/
{
        printf("\n�����%d���ߵĵ�1�����㣺",k+1);
        scanf("%s",vex1);
        printf("�����%d���ߵĵ�2�����㣺",k+1);
        scanf("%s",vex2);
        i=Locate(G,vex1);j=Locate(G,vex2); /*i,jΪ�ߣ�Vi,Vj���Ķ����Ӧ�������±� */

    s=(EdgeNode*) malloc (sizeof(EdgeNode));         /*�����µı߽��s */
    s->ivex=i;s->jvex=j;
    s->ilink= G-> adjmulist[i].firstedge; 
    s->jlink= G-> adjmulist[j].firstedge;        /*�Ա߽����и�ֵ*/
    G-> adjmulist[i].firstedge=s; 
    G-> adjmulist[j].firstedge=s;              /*����ڶ���������ͷ�Ĳ���*/
}
} 

void PrintGraph(AMLGraph *G)/*��ӡͼ�Ķ���ͱߵ���Ϣ*/
{
 int i,j;
 EdgeNode * s;
printf("\nͼ�ж������Ϊ��%d ",G->vexnum);
printf("\nͼ�б���Ϊ��%d ",G->edgenum);
printf("\nͼ�ж���Ϊ��");
for (i=0;i<G->vexnum;i++)
printf("%s ",G->adjmulist[i].vertex);

printf("\nͼ�ж�����ڽӶ���Ϊ��");
for(i=0;i<G->vexnum;i++)
{printf("\n%s: ",G->adjmulist[i].vertex);
s=G->adjmulist[i].firstedge;
while(s)
{
if((s->ivex)==i)
{printf("%s ",G->adjmulist[s->jvex].vertex);
s=s->ilink;
}
else
{printf("%s ",G->adjmulist[s->ivex].vertex);
s=s->jlink;
}
}
}

}

main()
{
 /* �˴�������Լ��Ĵ��� */
 AMLGraph amlg;
 CreateAMLG(&amlg);
 PrintGraph(&amlg);
getch();
}
