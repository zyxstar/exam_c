/* ==================Program Description================== */
/* �������ƣ�SelectSort.cpp                                   */
/* ����Ŀ�ģ�ֱ��ѡ������               */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/  
# include <conio.h>
# define MAXSIZE 20
typedef int RedType;

typedef struct            /*���� SqList*/
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;

void SelectSort(SqList *L)        /*SelectSort() �Ӻ���*/
{   int i,j,k,temp;
    for(i=1;i<L->length;++i)    /*ѡ���i��С�ļ�¼,��������λ*/
    {   k=i;
        for(j=i+1;j<=L->length;++j) /*��L.r[i..length]��ѡ��ֵ��С�ļ�¼*/
            if(L->r[j]<L->r[k])
                k=j;
        if(i!=k)
        {   temp=L->r[i];        /*���i����¼����*/
            L->r[i]=L->r[k];
            L->r[k]=temp;
        }
    }
}/*SelectSort() end */

void main()            /*main() ����*/ 
{  int i;
   SqList L;
   printf("SelectSort.cpp \n");
   printf("==============\n");
   printf("Please input the length of SqList (eg,5): ");
   scanf("%d",&L.length);
   for(i=1;i<=L.length;++i)
   {   printf("Please input the %d th element of SqList (eg,58): ",i);
      scanf("%d",&L.r[i]);
   }
   printf("\n");
   printf("The disordered : ");        /*δ��������Ա�*/
   for(i=1;i<=L.length;i++)
       printf("%d  ", L.r[i]);
   SelectSort(&L);                       /*���� SelectSort()*/
    printf("\n");
   printf("The sorted     : ");        /*���������Ա�*/
   for(i=1;i<=L.length;i++)
     printf("%d  ",L.r[i]);
   getch();
} /*main() end*/ 

