/* ==================Program Description================== */
/* �������ƣ�MergeSort.cpp                                 */
/* ����Ŀ�ģ��鲢����               */
/* Written By Cheng Zhuo                                  */
/* ========================================================*/


#include <conio.h>

#define MAXSIZE 20
#define LENGTH 7
typedef int RedType;

typedef struct                /*���� SqList*/
{   RedType    r[MAXSIZE+1];    
    int length;
}SqList;
typedef SqList RcdType;

void Merge(RcdType *SR,RcdType *TR,int i,int m,int n)/*Merge() �Ӻ���*/
/*�������SR[i..m]�������SR[m+1..n]�鲢Ϊ�����TR[i..n]*/
{   int j,k;
    for(j=m+1,k=i;i<=m&&j<=n;++k)    /*��SR�еļ�¼��С����ز���TR*/
    {   if(SR->r[i]<=SR->r[j])
            TR->r[k]=SR->r[i++];
        else
            TR->r[k]=SR->r[j++];
    }
    while(i<=m)               /*��ʣ���SR[i..m]���Ƶ�TR*/
       TR->r[k++]=SR->r[i++];
    while(j<=n)                /*��ʣ���SR[j..n]���Ƶ�TR*/
       TR->r[k++]=SR->r[j++];
}/*end of Merge() function*/

void MSort(RcdType *SR,RcdType *TR1,int s, int t)/*MSort() �Ӻ���*/
/*��SR[s..t]�鲢����ΪTR1[s..t]*/
{  int m;
   RcdType TR2;
   if(s==t)
     TR1->r[s]=SR->r[t];
   else
   {  m=(s+t)/2;            /*��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]*/
      MSort(SR,&TR2,s,m);    /*�ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]*/
      MSort(SR,&TR2,m+1,t);    /*�ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]*/
      Merge(&TR2,TR1,s,m,t);   /*��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]*/
   }/*end of else */
}/*end of MSort() function*/

void MergeSort(SqList *L)    /*MergeSort() ����*/
/* ��˳���L���鲢����*/
{
   MSort(L,L,1,L->length);
}/*end of MergeSort() ����*/

void main()                    /*main ���� */
{  int i;
   SqList L;
   printf("MergeSort.cpp \n");
   printf("============= \n");
   printf("Please input the length of SqList L: <eg,8>:");
   scanf("%d",&L.length);
  /* printf("Please input the disordered array L.r: ");*/
   for(i=1;i<=L.length;++i)
        {   printf("Please input the %d th element of SqList (eg,58):",i);
            scanf("%d",&L.r[i]);
        }
   printf("\n");
   printf("The disordered : ");        /*δ��������Ա�*/
   for(i=1;i<=L.length;i++)
       printf("%d ",L.r[i]);
   printf("\n");
   MergeSort(&L);                        /*���� MergeSort()*/
   printf("The sorted     : ");        /*������*/
   for(i=1;i<=L.length;i++)
       printf("%d ",L.r[i]);
   getch();
}                                     /*main() end */

