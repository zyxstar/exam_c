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

void HeapAdjust(HeapType *H,int s,int m) /*HeapAdjust() �Ӻ���*/
{  int temp,j;
   temp=H->r[s];
   for(j=2*s;j<=m;j*=2)
   {  if(j<m && (H->r[j]<H->r[j+1]))
        ++j;
      if(!(temp<H->r[j]))
        break;
      H->r[s]=H->r[j];
      s=j;
   }
   H->r[s]=temp;
} /*HeapAdjust() end*/

void HeapSort(HeapType *H)          /*HeapSort() �Ӻ��� */
{  int i,temp;
   for(i=H->length/2;i>=1;--i)
       HeapAdjust(H,i,H->length);        /*��H.r[1..H.length]����ɶ�*/
   for(i=H->length;i>=1;--i)
   {  temp=H->r[1];                    /*�ѶѶ���¼��δ�������������*/
      H->r[1]=H->r[i];                /*H.r[1..i]�е����һ����¼�ཻ��*/
      H->r[i]=temp;
      HeapAdjust(H,1,i-1);            /*��H.r[1,i-1]���µ���Ϊ��*/
   }
}/*HeapSort() end */

void main()                           /*main() ����*/
{  int i;
   HeapType H;
   printf("HeapSort.cpp\n");
   printf("============\n");
   printf("Please input the length of SqList (eg,5): ");
   scanf("%d",&H.length);
   for(i=1;i<=H.length;++i)
   {   printf("Please input the %d th element of SqList (eg,58): ",i);
       scanf("%d",&H.r[i]);
   }
   printf("\n");
   printf("The disordered : ");    /*δ����֮ǰ */
   for(i=1;i<=H.length;i++)
       printf("%d  ",H.r[i]);
   HeapSort(&H);                        /*���� HeapSort()*/
  printf("\n");
  printf("The sorted     : ");    /*����֮��*/
   for(i=1;i<=H.length;i++)
       printf("%d  ",H.r[i]);
   getch();
} /*main() end*/

