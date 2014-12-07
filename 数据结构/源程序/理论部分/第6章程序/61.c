      /* ==================Program Description================== */
/* �������ƣ�HeapSort.cpp                                  */
/* ����Ŀ�ģ�������               */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/
# include <conio.h>
# define MAXSIZE 20
typedef int RedType;

typedef struct                        /*���� SqList*/
{   RedType    r[MAXSIZE+1];
    int length;
}SqList;
typedef SqList HeapType;

void HeapAdjust(sqlist r,int l,int m) /*����Ԫ��r[1]~r[n]*/
{  int i,j;
   struct rec x;
   i=1;
   j=2*i;
   x=r[i];
   while (j<=m)
 {
    if (j<m && r[j].key<r[j+1].key) j++;
    if (x.key<r[j].key)
    {
      r[i]=r[j];
      i=j;
      j=2*i;
     }
     elst j=m+1;
    }
    r[i]=x;
} /*HeapAdjust() end*/

void HeapSort(sqlist r, int n)          /*HeapSort() �Ӻ��� */
{
   int i;
   struct rec m;
   for(i=n/2;i>=1;i--) HeapAdjust(r,i,n);
      for (i=n;i>=2;i--)
      {
        m=r[i];
        r[i]=r[1];
        r[1]=m;
        HeapAdjust((r,1,i-1);
       }
 }



void main()                           /*main() ����*/
{  int i;
   HeapType r;
   printf("HeapSort.cpp\n");
   printf("============\n");
   printf("Please input the length of SqList (eg,5): ");
   scanf("%d",&r.length);
   for(i=1;i<=r.length;++i)
   {   printf("Please input the %d th element of SqList (eg,58): ",i);
       scanf("%d",&r.r[i]);
   }
   printf("The disordered : ");    /*δ����֮ǰ */
   for(i=1;i<=r.length;i++)
       printf("%d  ",r.r[i]);
   HeapSort(&r);                        /*���� HeapSort()*/
  printf("\n");
  printf("The sorted     : ");    /*����֮��*/
   for(i=1;i<=H.length;i++)
       printf("%d  ",H.r[i]);
   getch();
} /*main() end*/

