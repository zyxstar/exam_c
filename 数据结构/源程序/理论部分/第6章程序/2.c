/* ==================Program Description================== */
/* �������ƣ�Shellinert.cpp                                     */
/* ����Ŀ�ģ�ϣ������                */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/  

# include <conio.h>
# define MAXSIZE 20
# define OK 1
# define ERROR 0
typedef int RedType;

typedef struct                        /*���� SqList*/
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;

void Shellinsert(SqList *L,int dk)     /*Shellinsert() �Ӻ���*/
/*��˳���L��һ��ϣ����������.������,��¼����Ϊdk,L.r[0]���ݴ�Ԫ��*/
{  int i,j;
   for(i=dk+1;i<=L->length;++i)
       if(L->r[i]<L->r[i-dk])       /*��Ҫ��L.r[i]���뵽���������ӱ�*/
       {    L->r[0]=L->r[i];            /*�ݴ���L.r[0]*/
            for(j=i-dk;j>0&&(L->r[0]<L->r[j]);j-=dk)
                L->r[j+dk]=L->r[j];    /*��¼���� */
            L->r[j+dk]=L->r[0];        /*���뵽��ȷ��λ��*/
       }
}

void main()                            /*main() ����*/
{  int i,dk=5;
   SqList L;/*={{0,49,38,65,97,76,13,27,49,55,4},10};*/
  printf("Shellinsert.cpp \n");
   printf("=============== \n");
   printf("Please input the length of SqList (eg, 5):  ");
   scanf("%d",  &L.length);                       /*�������Ա�*/
   printf("\n");
   for(i=1;i<=L.length;++i)
   {   printf("Please input the %d th integer (eg,58): ", i);
       scanf("%d", &L.r[i]);            /*�������Ա�Ԫ��,����L.r[0]���ڱ�*/
   }
   printf("The disordered : ");
   for(i=1;i<=L.length;i++)
       printf("%d ",L.r[i]);
   Shellinsert(&L,dk);                   /*���� Shellinsert()*/
   printf("\n");
   printf("The once ShellSorted sorted: ");
   for(i=1;i<=L.length;i++)
     printf("%d ",L.r[i]);
   printf("\n");
   getch();
} /*main() end */

