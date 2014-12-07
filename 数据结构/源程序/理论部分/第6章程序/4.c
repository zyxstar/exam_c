/* ==================Program Description================== */
/* �������ƣ�QuickSort.cpp                                    */
/* ����Ŀ�ģ���������               */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/  
# include <conio.h>
# define MAXSIZE 20
typedef int RedType;
typedef struct                    /*���� structure */
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;

int  Partition(SqList *L,int low,int high)    /*Partition() �Ӻ��� */
{  int pivotkey;
   L->r[0]=L->r[low];            /*���ӱ�ĵ�һ����¼��"��Ŧ"��¼*/
   pivotkey=L->r[low];        /*pivotkey����Ŧ�ļ�¼�ؼ���*/
   while(low<high)            /*�ӱ�����˽�������м�ɨ��*/
      {  while(low<high&&L->r[high]>=pivotkey)
        --high;
     L->r[low]=L->r[high];    /*��"��Ŧ"С�ļ�¼�Ƶ��׶�*/
     while(low<high&&L->r[low]<=pivotkey)
        ++low;                
     L->r[high]=L->r[low];    /*��"��Ŧ"��ļ�¼�Ƶ��߶�*/
      }
   L->r[low]=L->r[0];            /*"��Ŧ"��¼��λ*/
   return (low);            /*����"��Ŧ"λ��*/
} /*Partition() end */

void Qsort(SqList *L,int low,int high)    /*Qsort() sub-function */
{  int pivotloc;
   if(low<high)                    /*���ȴ���1*/
   {  pivotloc=Partition(L,low,high);
      Qsort(L,low,pivotloc-1);
      Qsort(L,pivotloc+1,high);
   }
}

void QuickSort(SqList *L)        /*QuickSort() �Ӻ���*/
{  Qsort(L,1,L->length);            /*���� Qsort()*/
}

void main()                        /*main() ����*/
{  int i;
   SqList L;
  printf("QuickSort.cpp \n");
  printf("============= \n");
  printf("Please input the length of SqList (eg,5): ");
   scanf("%d" ,&L.length);
   for(i=1;i<=L.length;++i)
   {   printf("Please input the %d th element of SqList (eg,58):",i );
       scanf("%d",&L.r[i]);
   }
   printf("\n");
   printf("The disordered : ");         /*����֮ǰ�����Ա�*/
   for(i=1;i<=L.length;i++)
       printf("%d  ", L.r[i]);
   QuickSort(&L);                /*���� QuickSort()*/
   printf("\n");
   printf("The sorted     : ");        /*����֮������Ա�*/
   for(i=1;i<=L.length;i++)
     printf("%d  ",L.r[i]);
   getch();
}                               /*main() end */

