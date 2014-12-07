/* ����ͼ��ʮ�������ʾ*/

#include "Stdio.h"
#include "Conio.h"
#define  MaxNum 50
    typedef struct ArcNode {/*���廡������ͣ����費���ǻ��ϵ�Ȩֵ���뻡��ص���Ϣ*/
    int tailvex,headvex;  /*��β����ͻ�ͷ�����λ��*/
    struct  ArcNode  * hlink, *tlink; /*ָ����ָ����ͬ��ͷ�ͻ�β��������*/
    }ArcNode;
    typedef struct VexNode {/*���嶥��������*/
    char vertex[3] ;      /*����ֵ������Ϊ�ַ����飬2���ַ�����*/
    ArcNode  *firstin, *firstout;  /*�ֱ�ָ��ö����һ���뻡�ͳ���*/
    }VexNode;
    typedef struct {/*����ʮ������洢��ͼ����*/
    VexNode vlist[MaxNum]; /*�����*/
    int  vexnum,arcnum;  /*����ͼ�еĶ������ͻ���*/
}OLGraph;

int Locate(OLGraph *G,char vex[])  /*ȷ��������ͼG�е�λ�ã�����G->V�е����*/
{
int i;
for(i=0;i<G->vexnum;i++)
if(strcmp(G->vlist[i].vertex,vex)==0)
return i;
}

void CreateOLG(OLGraph *G) /*����ʮ�������ʾ����������ͼG*/
{  
int i,j,k;
char vex1[3],vex2[3];
ArcNode * s;
printf("��������ͼ�Ķ������ͻ������ö��ŷָ�����\n");
scanf ("%d,%d",&(G->vexnum),&(G->arcnum)); 
        printf("���붥����Ϣ(������2���ַ�)��\n");
for (i=0;i<G->vexnum;i++)                       /*���������*/
        { 
scanf("\n%s",G->vlist[i].vertex);                 /*����ÿ������ı�ʶ��Ϣ*/
     G->vlist[i].firstin=NULL;G->vlist[i].firstout =NULL;  /*��ʼ��ָ��*/
        }
       for(k=0;k<G->arcnum; k++)                        /*����e����������ʮ������*/
        {
         printf("\n�����%d���ߵĵ�1�����㣺",k+1);
        scanf("%s",vex1);
        printf("�����%d���ߵĵ�2�����㣺",k+1);
        scanf("%s",vex2);
        i=Locate(G,vex1);j=Locate(G,vex2); /*i,jΪ��<Vi,Vj>�Ķ����Ӧ�������±� */

         s=(ArcNode*) malloc (sizeof(ArcNode));            /*�����µĻ����s */
         s->tailvex=i;s->headvex=j;
         s->hlink=G->vlist[j].firstin;
         s->tlink=G->vlist[i].firstout;
         /*
         *s={ i,j,G->vlist[j].firstin,G->vlist[i].firstout};        �Ի������и�ֵ*/
                                                     /*{tailvex,headvex,hlink,tlink}*/
         G->vlist[j].firstin=G->vlist[i].firstout=s;             /*������뻡�ͳ���������ͷ�Ĳ���*/
        }
}
void PrintGraph(OLGraph *G)/*��ӡͼ�Ķ���ͱߵ���Ϣ*/
{
 int i,j;
 ArcNode * s;
printf("\nͼ�ж������Ϊ��%d ",G->vexnum);
printf("\nͼ�б���Ϊ��%d ",G->arcnum);
printf("\nͼ�ж���Ϊ��");
for (i=0;i<G->vexnum;i++)
printf("%s ",G->vlist[i].vertex);

printf("\nͼ�ж�����ڽӶ���Ϊ��");
for(i=0;i<G->vexnum;i++)
{printf("\n%s: ",G->vlist[i].vertex);
s=G->vlist[i].firstout;
while(s)
{printf("%s ",G->vlist[s->headvex].vertex);
s=s->tlink;
}
}

printf("\nͼ�ж�������ڽӶ���Ϊ��");
for(i=0;i<G->vexnum;i++)
{printf("\n%s: ",G->vlist[i].vertex);
s=G->vlist[i].firstin;
while(s)
{printf("%s ",G->vlist[s->tailvex].vertex);
s=s->hlink;
}
}

}

main()
{
 /* �˴�������Լ��Ĵ��� */
 OLGraph olg;
 CreateOLG(&olg);
 PrintGraph(&olg);
getch();
}
