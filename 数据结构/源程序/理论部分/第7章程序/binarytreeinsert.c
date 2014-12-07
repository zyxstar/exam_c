
/* ==================Program Description================== */
/* �������ƣ�binarytreeinsert.c                                       */
/* ����Ŀ�ģ�����*rootΪ�����Ķ����������ϲ��ҹؼ��ֵ���kx�ļ�¼*/
/* Written By Mao Yifei                                  */
/* ========================================================*/
    #include "stdio.h"
    typedef struct bst/*��������������ṹ*/
    {
      int key; /*�ؼ����ֶΣ����������Ρ��ַ����͡��ṹ���͵�*/
      struct bst *leftchild; /*������*/
      struct bst *rightchild;/*������*/
    } bstnode;
    int bstinsert(bstnode **root,int kx)
    /*����*rootΪ�����Ķ����������ϲ��ҹؼ��ֵ���kx�ļ�¼��ָ��value��¼�ڶ������������Ƿ���ڴ����ҵ�kxֵ������ڣ�����ֵ1�����򷵻�ֵ0���������ظ����ָ��*/
   {
      bstnode *point;/*����ָ��point����ʼָ������root;*/
      bstnode *parent;/*����ָ��parent������ָ��point���ĸ����*/
      int flag;/*��Ǳ��������ڱ��point��parent�����ӻ����ӽ�㡣��Ϊ���ӽ��flagֵ��Ϊ0����Ϊ���ӽ��flagֵ��Ϊ1*/
      point=*root;
      parent=NULL;
      while(point!=NULL)/*��pָ���������Ϊ��*/
      {
        if(point->key==kx)/*�������ؼ��ֵ��ڸ���ֵkx�����ҳɹ�*/
        {
          return 1;
        }/*endif*/
        if(point->key<kx) /*�������ؼ���С�ڸ���ֵkx*/
        {
          parent=point;
          point=point->rightchild;/*���������ϼ������в���*/
          flag=1;/*���pointΪparent�����ӽ��*/
        }/*endif*/
        else
        {
          parent=point;
          point=point->leftchild; /*�������ؼ��ִ��ڸ���ֵkx�����������ϼ������в���*/
          flag=0; /*���pointΪparent�����ӽ��*/
        }/*endif*/
      }/*����ʧ�ܣ�����ؼ���Ϊkx���½����pointָ�봦*/
      point=(bstnode *)malloc(sizeof(bstnode));/*Ϊ�½�����ռ�*/
      point->key=kx;/*���ؼ���ֵΪkx*/
      point->leftchild=NULL;/*�½��ΪҶ�ӽ��*/
      point->rightchild=NULL;
      if(parent==NULL)/*���ԭ����������Ϊ��*/
        *root=point;/*�½���Ϊ�����*/
      else
      {
        if(flag==0) /*�½��Ϊ�ϲ�������ӽ��*/
          parent->leftchild=point;
        else /*�½��Ϊ�ϲ�������ӽ��*/
          parent->rightchild=point;
      }/*endelse*/
      return 0;/*�����½���ָ��*/
    }/* bstinsert��������*/
    void inorder(bstnode *root) /*���������rootΪ�����Ķ���������*/
    {
      bstnode *point;
      point=root;
      if(point!=NULL)
      {
        inorder(point->leftchild);
        printf("%d ",point->key);
        inorder(point->rightchild);
      }/*endif*/
    }/*inorder��������*/
    main()
    {
      bstnode *root;
      int kx,flag;
      root=NULL;
      while(1)
      {
        printf("please input the data you want to search:(zero will exit)\n");
        scanf("%d",&kx);  /*��������ҵ�ֵkx*/
        if(kx==0) /*����ֵΪ0���������*/
           break;
        flag=bstinsert(&root,kx); /*���Ҷ���������root�Ƿ���ڵ���kxֵ�Ľڵ�*/
        if(flag==1)  /*�ҵ���*/
          printf("the data is found\n");
        else     /*δ�ҵ�*/
          printf("the data is not found and it has been inserted into the tree\n");
        printf("the inorder traversal of the tree is:");
        inorder(root);/*��������������������*/
        printf("\n");
      }
    }

