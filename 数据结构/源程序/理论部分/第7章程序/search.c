/* ==================Program Description================== */
/* �������ƣ�search.c                                       */
/* ����Ŀ�ģ���r[n]�����в��ҹؼ��ֵ���kx�ļ�¼                */
/* Written By Mao Yifei                                  */
/* ========================================================*/

    #include "stdio.h"
    #define max 7
    int searchlist[max]={0,13,25,16,23,57,66};
    int s_search(int r[],int n,int kx)
    /*��r[n]�����в��ҹؼ��ֵ���kx�ļ�¼�����ҵ����ظ�Ԫ���������е��±꣬���򷵻�0*/
        {
           int i;
           r[0]=kx;/*���±�Ϊ0�����ü�����*/
           i=n-1;
      while(r[i]!=kx)
        i--;
      return i;/*���ز��ҵ�λ��*/
    }
    main()
    {
      int key;
      printf("please input the data you want to search:\n");
      scanf("%d",&key);/*����Ҫ���ҵĹؼ���key*/
      if(s_search( searchlist,max, key)!=0)/*�������ֵ������0�������ҳɹ�*/
         printf("the data is found ");
      else  /*����ʧ��*/
         printf("the data is not found");
    }

