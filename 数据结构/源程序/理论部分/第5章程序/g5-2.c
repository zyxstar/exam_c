/* ͼ���ڽӱ��ʾ*/

#include "Stdio.h"
#include "Conio.h"

#define MaxNum 50          /*ͼ����󶥵���Ϊ50*/
typedef struct enode{               /*�߽��ṹ����*/
          int adjvex;                   /*�ڽӵ���*/
          struct enode  * next;         /*ָ����ָ����һ���߽��*/
          /*������ͼ����Ӧ����һ����ʾȨֵ����weight*/
         }EdgeNode;        
    typedef struct vnode{              /*������ṹ����*/
          char vertex[3];          /*����������Ϊ�ַ����飬2���ַ�����*/
          EdgeNode  * firstedge;      /*ָ����ָ���һ���߽��*/
         }VexNode;       
    typedef VexNode AdjList[MaxNum];  /*�ڽӱ����Ͷ���*/
    typedef struct{  
         AdjList adjlist;                /*�ڽӱ�*/
         int n,e;                     /*�������ͱ���*/
        }ALGraph;                   /*ALGraph�����ڽӱ�ʽ�洢��ͼ����*/
int Locate(ALGraph *G,char vex[])  /*ȷ��������ͼG�е�λ�ã�����G->V�е����*/
{
int i;
for(i=0;i<G->n;i++)
if(strcmp(G->adjlist[i].vertex,vex)==0)
return i;
}
void CreateALGraph(ALGraph *G)
     {/*��������ͼ���ڽӱ�洢*/
       int i,j,k;
       char vex1[3],vex2[3];
       EdgeNode * s;
       printf("����ͼ�Ķ������ͱ���(�ö��ŷָ�)��\n");
       scanf("%d,%d",&(G->n),&(G->e));  /*��������Ķ������ͱ���*/
       printf("���붥����Ϣ(������2���ַ�)��\n");
       for (i=0;i<G->n;i++)              /*����n������Ķ�������*/
      {scanf("\n%s",G->adjlist[i].vertex);    /*����ÿ������ı�ʶ��Ϣ*/
      G->adjlist[i].firstedge=NULL;       /*������ڽӱ�ͷָ����Ϊ��*/
       }
       printf("\n����ͼ��ÿ��������������������ĵı�ʶ��Ϣ: ");
       for (k=0;k<G->e;k++)         /*����e���߽����ڽӱ�*/
        {
        printf("\n�����%d���ߵĵ�1�����㣺",k+1);
        scanf("%s",vex1);
        printf("�����%d���ߵĵ�2�����㣺",k+1);
        scanf("%s",vex2);
        i=Locate(G,vex1);j=Locate(G,vex2); /*i,jΪ�����ڶ��������е��±�  */

      s=(EdgeNode*)malloc(sizeof(EdgeNode));  /*�����µı߽��s*/
      s->adjvex=j;                          /*�ڽӵ����Ϊj*/
      s->next=G->adjlist[i].firstedge;           /*���µı߽��s���뵽����Vi���ڽӱ�ͷ��*/
      G->adjlist[i].firstedge=s;
       }
}

void PrintGraph(ALGraph *G)/*��ӡͼ�Ķ���ͱߵ���Ϣ*/
{
 int i,j;
 EdgeNode * s;
printf("\nͼ�ж������Ϊ��%d ",G->n);
printf("\nͼ�б���Ϊ��%d ",G->e);
printf("\nͼ�ж���Ϊ��");
for (i=0;i<G->n;i++)
printf("%s ",G->adjlist[i].vertex);

printf("\nͼ�ж�����ڽӶ���Ϊ��");
for(i=0;i<G->n;i++)
{printf("\n%s: ",G->adjlist[i].vertex);
s=G->adjlist[i].firstedge;
while(s)
{printf("%s ",G->adjlist[s->adjvex].vertex);
s=s->next;
}
}

}

main()
{
 /* �˴�������Լ��Ĵ��� */
 ALGraph alg;
 CreateALGraph(&alg);
 PrintGraph(&alg);
getch();
}
