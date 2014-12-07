/* AOV������������,ͼ�Դ���ȵ��ڽӱ��ʾ*/

#include "Stdio.h"
#include "Conio.h"

#define MaxNum 50          /*ͼ����󶥵���Ϊ50*/

typedef struct
{
int elem[MaxNum];
int top;
}sqstacktp;

void ini_sqstack(sqstacktp *s)/*��ʼ��ջ*/
{
    s->top=0;
}

int empty_sqstack(sqstacktp *s)/*�ж�ջ�Ƿ�Ϊ��*/
{
    if((*s).top>0)
    {
        return(0);
    }
    else
    {
        return(1);
    }
}

void push_sqstack(sqstacktp *s,int x)/*��ջ*/
{
 if((*s).top==MaxNum)/*��ջsδ������Ԫ��xѹ��ջ�У�����ջ��״̬���䲢����������Ϣ*/
    printf("Overflow");
 else
          {
           (*s).elem[(*s).top]=x;     /*x��ջ*/
           (*s).top++;      /*ջ��ָ���1*/
           }
}


int pop_sqstack(sqstacktp *s)/*��ջ*/
    {
        if((*s).top==0)/*��ջs���գ���ɾȥջ��Ԫ�ز�����Ԫ��ֵ�����򷵻ؿ�Ԫ��NULL*/
          return(NULL);
        else{
           (*s).top--;          /* ջ��ָ���1*/
           return((*s).elem[(*s).top]);   /*����ԭջ��Ԫ��ֵ*/
        }
}

typedef struct enode{               /*�߽��ṹ����*/
          int adjvex;                   /*�ڽӵ���*/
          struct enode  * next;         /*ָ����ָ����һ���߽��*/
          /*������ͼ����Ӧ����һ����ʾȨֵ����weight*/
         }EdgeNode;        
    typedef struct vnode{             /*������ṹ����*/
          char vertex[3];             /*����������Ϊ�ַ����飬2���ַ�����*/
          int indegree;               /*���涥����ȵ�������*/
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
      G->adjlist[i].indegree=0;           /*��ʼ����������Ϊ0*/
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

      s=(EdgeNode*)malloc(sizeof(EdgeNode));/*�����µı߽��s*/
      s->adjvex=j;                          /*�ڽӵ����Ϊj*/
      s->next=G->adjlist[i].firstedge;      /*���µı߽��s���뵽����Vi���ڽӱ�ͷ��*/
      G->adjlist[i].firstedge=s;
      G->adjlist[j].indegree++;             /*��ͷ����vj�������1*/
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

void TopoSort(ALGraph *G)
{
int i,j,k,count;
EdgeNode * p;
sqstacktp stack;
ini_sqstack(&stack);

for(i=0;i<G->n;i++)
if(G->adjlist[i].indegree==0)
    push_sqstack(&stack,i);

count=0;  /*������������*/
printf("\n������������Ϊ: ");
while(!empty_sqstack(&stack))
{
j=pop_sqstack(&stack);
printf("%s ",G->adjlist[j].vertex);
count++;
p=G->adjlist[j].firstedge;
while(p!=NULL)
{
k=p->adjvex;
G->adjlist[k].indegree--;
if(G->adjlist[k].indegree==0)
    push_sqstack(&stack,k);
p=p->next;
}
}

if(count<G->n)
printf("\n��ʾ:��AOV����������!");

}

main()
{
 /* �˴�������Լ��Ĵ��� */
 ALGraph alg;
 CreateALGraph(&alg);
 PrintGraph(&alg);
 TopoSort(&alg);
getch();
}
