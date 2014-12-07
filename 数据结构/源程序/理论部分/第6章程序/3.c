/* ==================Program Description================== */
/* �������ƣ�BubbleSort.cpp                                     */
/* ����Ŀ�ģ�ð������                */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/  
# include <conio.h>
# include <stdio.h>
# define MAXSIZE 20
# define MAX_LENGTH 100
typedef int RedType;
typedef struct            /*���� SqList */
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;

void BubbleSort(SqList *L)
{   int i,j,temp;
    for(i=0;i<=L->length;++i)
       for(j=L->length-1;j>i;--j)
           if(L->r[j+1]<L->r[j])
           {    temp=L->r[j+1];        /*����L.r[j+1]��L.r[j]*/
                L->r[j+1]=L->r[j];
                L->r[j]=temp;
           }
}                                      /*BubbleSort() end*/

void main()                            /*main() ����*/
{  int i;
   SqList L;
   printf("BubbleSort.cpp \n");
   printf("==============\n");
   printf("Please input the length of SqList (eg,6): ");
   scanf("%d" ,&L.length);
   for(i=1;i<=L.length;++i)
   {   printf("Please input the %d th element of SqList (eg,23): ",i);
       scanf("%d",&L.r[i]);
   }
   printf("\n");
   printf("The disordered : ");         /*δ��������Ա�*/
   for(i=1;i<=L.length;i++)
       printf("%d  ", L.r[i]);

   BubbleSort(&L);                        /*���� BubbleSort()*/
   printf("\n");
   printf("The ordered    : ");  
   for(i=1;i<=L.length;i++)               /*���������Ա�*/
          printf("%d  ",L.r[i]);
   getch();
}                                       /*main() end*/

