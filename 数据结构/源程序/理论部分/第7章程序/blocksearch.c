/* ==================Program Description================== */
/* �������ƣ�blocksearch.c                                       */
/* ����Ŀ�ģ��ֿ�������slist��Ϊn�����ұ�Ϊr[]�����ҹؼ��ֵ���kx������Ԫ��*/
/* Written By Mao Yifei                                  */
/* ========================================================*/
    #include "stdio.h"
    #define max 14
    #define m 3
    int searchlist[max]={14,31,8,22,18,43,62,49,35,52,88,78,71,83};
    int slist[m][2]={31,0,62,5,88,10};
    int block_search(int r[],int slist[][2],int kx,int n)
    /*�ֿ�������slist��Ϊn�����ұ�Ϊr[]�����ҹؼ��ֵ���kx������Ԫ�أ�����Ԫ�ؾ����±�Ϊ0���洢*/
    {
      int i,flag;
    int lowlim,highlim;/*����ֿ���ҵ���������*/
    i=0;
    while((slist[i][0]<kx)&&(i<n))
    i++;
    if(slist[i][0]<kx)/*���һ���ֿ�����ֵ��Ҫ���ҵ�kx��С*/
    return 0;
    if(i==2)/*�����һ���ֿ��в��ҹؼ���kx*/
    {
      lowlim=slist[2][1];
      highlim=13;
    }
    else
    {
      lowlim=slist[i][1];
      highlim=slist[++i][1]-1;
    }
    i=lowlim;
    while(i<=highlim)/*�ڷֿ��в�������Ԫ��*/
    {
      if(r[i]==kx) /*�ҵ���*/
        return i;
      else
        i++;
    }
    /*δ�ҵ��ˣ�����ֵ0*/
    return 0;
    }
    main()
    {
      int key;
      printf("please input the data you want to search:\n");
      scanf("%d",&key);/*����Ҫ���ҵĹؼ���key*/
      if(block_search(searchlist,slist,key,m)!=0)/*�������ֵ������0�������ҳɹ�*/
        printf("the data is found at %d",block_search(searchlist,slist,key,m));
      else  /*����ʧ��*/
        printf("the data is not found");
      getch();
    }

