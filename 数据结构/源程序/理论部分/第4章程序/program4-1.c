/*====================================================================*/
/*�������ƣ�traverse.c                                                */
/*����Ŀ�ģ��������ʽ����������������                              */
/* ===================================================================*/

#include "stdio.h"
#include "stdlib.h"
int GetValue(int oper,int oper1,int oper2) ;

typedef char TElemType;             /*����Ԫ������Ϊ�ַ���*/
typedef struct BTNode               /*����������Ķ�������ṹ*/
{TElemType data;                    /*��Ž������ݣ��ַ�����*/
struct BTNode *lchild, *rchild;     /*�������������ָ��*/
}BTNode;

/*--------------------------------------------------------------------*/
/*��������CreateBTree                                                 */
/*���ܣ�ʹ�õݹ齨��������                                            */
/*����˵����nodelist���ַ������ͣ�����ÿ���ַ���Ϊ��������һ�����    */
/*          i�����ͣ���ʾ����λ�ã����ַ���nodelist�е�λ��         */
/*����ֵ������ָ�������������ָ�룬                                */
/*        �������0���߽���������7���򷵻�NULL                      */
/*--------------------------------------------------------------------*/
BTNode * CreateBTree(char *nodelist,int i)
{
    BTNode *newnode; /*�����½��ָ��*/
    if(nodelist[i]==0||i>7)/*�ݹ����ֹ����*/
        return NULL;
    else
    {
        /*Ϊ�½������ڴ�ռ�*/
        newnode=(BTNode *)malloc(sizeof(BTNode));
        /*���ַ������½��*/
        newnode->data=nodelist[i];
        /*�ݹ齨��������*/
        newnode->lchild=CreateBTree(nodelist,2*i);
        /*�ݹ齨��������*/
        newnode->rchild=CreateBTree(nodelist,2*i+1);
        return newnode;/*���ظ�������λ��*/
    }
}
/*--------------------------------------------------------------------*/
/*��������PreTraverse                                                 */
/*���ܣ�������ǰ������ĵݹ��㷨                                      */
/*����˵����bt��ָ�����ָ�룬ָ��������ĸ���㣬��ʾһ�ö�����    */
/*����ֵ��û�з���ֵ                                                  */
/*--------------------------------------------------------------------*/

void PreTraverse(BTNode *bt)
{
    if(bt!=NULL)                    /*��������ֹ����*/
    {
        printf("%c",bt->data);      /*��ӡ�������*/
        PreTraverse(bt->lchild);      /*�ݹ����������*/
        PreTraverse(bt->rchild);     /*�ݹ����������*/
    }
}
/*--------------------------------------------------------------------*/
/*��������InTraverse                                                  */
/*���ܣ���������������ĵݹ��㷨                                      */
/*����˵����bt��ָ�����ָ�룬ָ��������ĸ���㣬��ʾһ�ö�����    */
/*����ֵ��û�з���ֵ                                                  */
/*--------------------------------------------------------------------*/
void  InTraverse(BTNode * bt)
{
    if(bt!=NULL)                    /*��������ֹ����*/
    {
        InTraverse(bt->lchild);       /*�ݹ����������*/
        printf("%c",bt->data);      /*��ӡ�������*/  
        InTraverse(bt->rchild);      /*�ݹ����������*/
    }
}
/*--------------------------------------------------------------------*/
/*��������PostTraverse                                                */
/*���ܣ���������������ĵݹ��㷨                                      */
/*����˵����bt��ָ�����ָ�룬ָ��������ĸ���㣬��ʾһ�ö�����    */
/*����ֵ��û�з���ֵ                                                  */
/*--------------------------------------------------------------------*/
void  PostTraverse(BTNode * bt)
{
    if(bt!=NULL)                    /*��������ֹ����*/
    {
        PostTraverse(bt->lchild);     /*�ݹ����������*/
        PostTraverse(bt->rchild);    /*�ݹ����������*/
        printf("%c",bt->data);      /*��ӡ�������*/
    }
}
/*--------------------------------------------------------------------*/
/*��������Calculate                                                   */
/*���ܣ�������ʽ���                                                */
/*����˵����bt��ָ�����ָ�룬ָ��������ĸ���㣬��ʾһ�ö�����    */
/*����ֵ�����ر��ʽ����Ľ��                                        */
/*--------------------------------------------------------------------*/
int Calculate(BTNode * bt)
{
    int oper1=0;/*ǰ������*/
    int oper2=0;/*�������*/
    if(bt->lchild==NULL && bt->rchild==NULL)
        return bt->data-48;
    else
    { 
        oper1=Calculate(bt->lchild);/*������*/
        oper2=Calculate(bt->rchild);/*������*/
        return (GetValue(bt->data,oper1,oper2));
    }
}
/*--------------------------------------------------------------------*/
/*��������GetValue                                                    */
/*���ܣ������������Ͳ�������������                                  */
/*����˵����oper�ǲ�������oper1��oper2������������                    */
/*����ֵ��û�з���ֵ                                                  */
/*--------------------------------------------------------------------*/
int GetValue(int oper,int oper1,int oper2)
{
    int result=0;
    switch((char)oper)
    { 
        case '*': result=oper1*oper2;return(result);
        case '/':result=oper1/oper2;return(result);
        case '+':result=oper1+oper2;return(result);
        case '-':result=oper1-oper2;return(result);
    }
}
/*--------------------------------------------------------------------*/
/*��������main                                                        */
/*���ܣ��������ʽ����������������                                  */
/*����˵�����޲���                                                    */
/*����ֵ��û�з���ֵ                                                  */
/*--------------------------------------------------------------------*/
void main()
{
    BTNode * root=NULL;                         /*�������ʽ������ָ��*/
    int result;                                 /*��������������*/
    /*��������������������*/
    char nodelist[8]={'-','+','*','/','4','8','6','2'};
    root=CreateBTree(nodelist,1);              /*�������ʽ������*/
    /*���ǰ׺���ʽ*/
    printf("\n ǰ׺���ʽPreTraverse expression:[");
    PreTraverse(root);
    printf("]\n");
    /*�����׺���ʽ*/
    printf("\n InTraverse expression:[");
    InTraverse(root);
    printf("]\n");
    /*�����׺���ʽ*/
    printf("\n PostTraverse expression:[");
    PostTraverse(root);
    printf("]\n");
    /*������ʽ���*/
    result=Calculate(root);
    printf("\n calculate result is [%2d]\n",result);
    getchar();
}
