
/* ==================Program Description================== */
/* �������ƣ�binarysearch.c                                       */
/* ����Ŀ�ģ���r[n]�����в��ҹؼ��ֵ���kx�ļ�¼                */
/* Written By Mao Yifei                                  */
/* ========================================================*/
    #include "stdio.h"
    #define max 13
    int searchlist[max]={0,5,7,12,25,34,37,43,46,58,80,92,105};
    int binary_search(int r[],int n, int kx)
    /*��r[n]�����в��ҹؼ��ֵ���kx�ļ�¼�����ҵ����ظ�Ԫ���������е��±꣬���򷵻�0*/
    {
      int mid,low,high;
      low=1;/*���ò�������*/
      high=n-1;
      while(low<=high)/*���ұ�ǿգ������۰����*/
     {
       mid=(low+high)/2;    /*ȡ�м�λ��*/
       if(kx<r[mid])     /*�����ڱ�����������*/
       high=mid-1;
       else if(kx>r[mid])  /*�����ڱ���Ұ�������*/
         low=mid+1;
       else return mid;
     }      /*���ҳɹ�������Ԫ��λ��*/
     return 0;              /*����ʧ�ܣ�����ֵ��1*/
    }
    main()
    {
     int key;
     printf("please input the data you want to search:\n");
     scanf("%d",&key);/*����Ҫ���ҵĹؼ���key*/
     if(binary_search(searchlist,max,key)!=0)/*�������ֵ������0�������ҳɹ�*/
      printf("the data is found ");
    else  /*����ʧ��*/
      printf("the data is not found");
    getch();
    }

