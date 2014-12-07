/* ������ȱ�������ͨͼ����������ɭ�֣�ͼʹ���ڽӱ�洢������ɭ��ʹ�ú����ֵ�����洢*/

#include "Stdio.h"
#include "Conio.h"
#include "string.h"
#define MaxNum 50     /*ͼ����󶥵���Ϊ50*/
int visited[MaxNum];  /*��Ƕ����������,Ԫ��ֵΪ0��ʾ�ö���δ����,Ϊ1��ʾ�ö����ѱ���*/

typedef struct CSNode{ /*����ɭ�ֵĺ����ֵ�����洢�ṹ*/
      char data[3];/*����������Ϊ�ַ����飬���2���ַ�����*/
      struct CSNode *firstchild, *nextsibling;
      } CSNode, *CSTree;

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

void  DFSTree(ALGraph *G,int v ,CSTree T)
{/*�ӵ�v���������������ȱ���ͼG��������*TΪ����������*/
 EdgeNode *w;
 CSTree p,q;
 int first;
 visited[v]=1; /*���v�ѷ���*/
 first=1; /*first�Ǳ��,Ϊ1��ʾ������������,Ϊ0��ʾ�������ӵ����ֵ�*/
 w=G->adjlist[v].firstedge;        /*��ȡv�ڽӱ��ͷָ��*/
 while(w)
 {
        if(!visited[w->adjvex])
         { p=(CSTree)malloc(sizeof(CSNode));       /*���亢�ӽ��*/
           strcpy(p->data,G->adjlist[(w->adjvex)].vertex);
           p->firstchild=NULL;
           p->nextsibling=NULL;
           if (first)            /*w��v�ĵ�һ��δ�����ʵ��ڽӶ��㣬��Ϊ�������ӽ��*/
            { T->firstchild=p;
              first=0;
            }
           else { /*w��v������δ�����ʵ��ڽӶ��㣬��Ϊ��һ�ڽӶ�������ֵ�*/
                q->nextsibling=p;           
                }
           q=p;
           DFSTree(G,w->adjvex,q);   /*�ӵ�w���������������ȱ���ͼG��������������*q*/
          }
w=w->next;

}
}

                                 
CSTree DFSForest(ALGraph *G)
{ /*��������ͼG�������������ɭ�ֵĺ����ֵ�����T*/
      int i;
      CSTree T,p,q;
      T=NULL;
      for (i=0;i<G->n;i++)
        visited[i]=0;                 /*��ʼ�����ʱ�־����*/
      for(i=0;i<G->n;i++)
        if (!visited[i])                       /*����iΪ�µ��������ĸ����*/
          { p=(CSTree )malloc(sizeof(CSNode)); /*��������*/
           strcpy(p->data,G->adjlist[i].vertex);
           p->firstchild=p->nextsibling=NULL;
            /*������㸳ֵ*/
            if (!T)  
                 T=p;                    /*T�ǵ�һ���������ĸ�*/
            else  q->nextsibling=p;            /*ǰһ�õĸ����ֵ��������������ĸ�*/
            q=p;                            /*qָʾ��ǰ�������ĸ�*/
            DFSTree(G,i,p);                 /*������pΪ����������*/
          }
     return T;
}

void PrintL(CSTree T)
{
CSTree child;
for(child=T->firstchild;child;child=child->nextsibling)
{
printf("(%s, %s) ",T->data,child->data);
PrintL(child);
}
}


void PrintForest(CSTree T)  /*��ӡ����ɭ���н��֮��ķ�֧������*/
{
if(T)
{
printf("\n");
PrintL(T);
PrintForest(T->nextsibling);
}

}

void Print_CSTreeLeft(CSTree T,int i)
{

int j;
CSTree p;
for(j=1;j<=i;j++)printf("  ");/*����i���ո��Ա��ֳ����*/
printf("%s\n",T->data);      /*��ӡԪ�أ�����*/
for(p=T->firstchild;p;p=p->nextsibling)
    Print_CSTreeLeft(p,i+1);     /*��ӡ����*/
}

void Print_CSTree(CSTree T,int i)/*���������ʽ��ӡ�������ɭ�ֵ�������Ԫ�أ�i��ʾ������ڲ�Σ����ε���ʱi=0*/
{
if(T)
{
printf("\n");
Print_CSTree(T->nextsibling,i+1);
Print_CSTreeLeft(T,i);

}
}

void Print_BiTree(CSTree T,int i) /*��ӡ����ɭ�ֵĽ��ṹ���Ժ����ֵ�����洢*/
{
int j;

if(T->nextsibling)Print_BiTree(T->nextsibling,i+1);
for(j=1;j<=i;j++)printf("  ");
printf("%s\n",T->data);
if(T->firstchild)Print_BiTree(T->firstchild,i+1);
}

/*
void InOrderTraverse_Tree(CSTree T��void(*visit)( CSTree ))
��{
����// �Ժ���-�ֵ��������洢�ṹ���������ָ��T��ָɭ��
CSTree *p;����
p=T; ��������������������������������������// ָ��pָ���һ�����ĸ�
����while (p) {
������InOrderTraverse_Tree(p->firstchild, visit); // �������*p������ɭ��
������visit(p); ����������������������// ͨ������ָ��*visit ���ʸ����*p
������p=p->nextsibling; ������������������������// ָ��p������һ�����ĸ�
����} // while
��}
*/

main()
{
 /* �˴�������Լ��Ĵ��� */
 ALGraph alg;
 CSTree T;
 CreateALGraph(&alg);
 /*PrintGraph(&alg);*/
 T=DFSForest(&alg);
 printf("��ӡ����ɭ�ֵĽ��ṹͼʾ��\n");
 Print_BiTree(T,0);
 printf("��ӡ����ɭ�ֵ�������\n");
 Print_CSTree(T,0);
 printf("��ӡ����ɭ���еĽ��֮��ķ�֧��\n");
 PrintForest(T);
getch();
}

