/* ==================Program Description================== */
/* �������ƣ�InsertSort.cpp                                      */
/* ����Ŀ�ģ�ֱ�Ӳ�������                 */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/  
/* # include <iostream.h> */ 
# include <conio.h>
# define MAXSIZE 20
# define MAX_LENGTH 100
typedef int RedType;

typedef struct                             /*���� SqList*/
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;

void InsertSort(SqList *L)                /*InsertSort() �Ӻ���*/
{  int i,j;
   for(i=2;i<=L->length;++i)
       if(L->r[i]<L->r[i-1])
       {    L->r[0]=L->r[i];              /*����Ϊ�ڱ�*/
            for(j=i-1;L->r[0]<L->r[j];--j)
                L->r[j+1]=L->r[j];        /*��¼����*/
            L->r[j+1]=L->r[0];            /*���뵽��ȷ��λ��*/
       }                                   
}                                         /*InsertSort() ����*/

void main()                               /*main() ����*/
{  int i;
   SqList L;
 printf("InsertSort.cpp \n");
   printf("============== \n");
   printf("Please input the length of SqList (eg, 5): ");
  scanf("%d",&L.length);                 /*�������Ա�*/

   for(i=1;i<=L.length;++i)
   {  printf("Please input the %d th integer (eg,58): ",i);
     scanf("%d",&L.r[i]);             /*�������Ա�Ԫ��,����L.r[0]���ڱ�*/
   }
   printf("The disordered : ");        /*���δ����֮ǰ�����Ա�*/
   for(i=1;i<=L.length;i++)
       printf("%d  ", L.r[i]);
   InsertSort(&L);                      /*���� InsertSort()   */
   printf("\n");
   printf("The ordered    : ");        /*�������֮������Ա�*/
   for(i=1;i<=L.length;i++)
    printf("%d  ",L.r[i]);
   getch();
}                                         /*main() end*/

