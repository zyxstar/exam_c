
/* ==================Program Description================== */
/* �������ƣ�balancedbinarytreeinsert.c                                       */
/* ����Ŀ�ģ�����ƽ�������                */
/* Written By Mao Yifei                                  */
/* ========================================================*/
    #include "stdio.h"
    typedef struct bst/*��������������ṹ*/
    {
      int key; /*�ؼ����ֶΣ����������Ρ��ַ����͡��ṹ���͵�*/
      struct bst *leftchild; /*������*/
      struct bst *rightchild;/*������*/
      int bf;/*ƽ������*/
    } bstnode;
    void L_Rotate(bstnode **p)/*����*pΪ���ڵ��������˳ʱ����ת�������*pָ��Ľڵ�Ϊ�������¸�*/
    {
      bstnode *lc;
      lc=(*p)->leftchild/*lcָ��*p�������ĸ��ڵ�*/;
      (*p)->leftchild=lc->rightchild;/*p���������ҽ�lc��������*/
      lc->rightchild=*p;
      *p=lc;/* *pָ���½ڵ�*/
    }
    void R_Rotate(bstnode **p) /*����*pΪ���ڵ����������ʱ����ת�������*pָ��Ľڵ�Ϊ�������¸�*/
    {
      bstnode *lc;
      lc=(*p)->rightchild; /*lcָ��*p�������ĸ��ڵ�*/;
      (*p)->rightchild=lc->leftchild; /*p���������ҽ�lc��������*/
      lc->leftchild=*p;
      *p=lc; /* *pָ���½ڵ�*/
    }
    void LeftBalance(bstnode **parent,bstnode **p,bstnode **root,int kx)
    /*���ؼ���ֵΪkx�Ĳ��뵽ƽ�������*root�У����������ڵ�����ķ�ƽ��ڵ�*pΪ���ڵ����������ƽ����ת������֮��*pָ��Ľڵ�Ϊ�������µĸ�,*parentָ��*p�ĸ��ڵ�*/
    {
      int flag=0;
      bstnode *lc;
      bstnode *lrc;
      if(*p==*root)/*�������ƽ���Ϊ���ڵ�*/
      flag=1;/*���ñ��*/
      lc=(*p)->leftchild;/*lcָ��*p�����������ڵ�*/
      if(lc->key>kx)/*�½ڵ������p������������������*/
      {
        (*p)->bf=0;/*�޸ĸ��ڵ�����������ƽ������*/
        lc->bf=0;
        L_Rotate(p);/*��˳ʱ����ת*/
      }
      else /*�½ڵ������p������������������*/
      /*������ʱ����ת����˳ʱ����ת*/
      {
        lrc=lc->rightchild;/*lrcָ��lc�����������ڵ�*/
        if(lrc->bf==1)/*����*p�������ӵ�ƽ������*/
        {
          (*p)->bf=0;
          lc->bf=1;
        }
        if(lrc->bf==0) /*����*p�������ӵ�ƽ������*/
        {
          (*p)->bf=0;
          lc->bf=0;
        }
        if(lrc->bf==-1) /*����*p�������ӵ�ƽ������*/
        {
          (*p)->bf=-1;
          lc->bf=0;
        }
        lrc->bf=0;
        R_Rotate(&((*p)->leftchild));/*������ʱ����ת*/
        L_Rotate(p);/*����˳ָ����ת*/
      }
      if(flag==1)/*����������Ǹ��ڵ��ƽ��*/
        *root=*p;/*����ǰ��ת��Ľڵ�����Ϊ���ڵ�*/
      else/**parentָ����ת��Ľڵ�*p*/
      {
        if((*parent)->key>(*p)->key)
          (*parent)->rightchild=*p;
        else
          (*parent)->leftchild=*p;
        }
      }
    void RightBalance(bstnode **parent,bstnode **p,bstnode **root,int kx)
    /*���ؼ���ֵΪkx�Ĳ��뵽ƽ�������*root�У����������ڵ�����ķ�ƽ��ڵ�*pΪ���ڵ����������ƽ����ת������֮��*pָ��Ľڵ�Ϊ�������µĸ�,*parentָ��*p�ĸ��ڵ�*/
    {
      int flag;
      bstnode *lc;
      bstnode *lrc;
      if(*p==*root)
        flag=1;
      lc=(*p)->rightchild;
      if(lc->key<kx)/*�½ڵ������p������������������*/
      {
        (*p)->bf=0;/*�޸ĸ��ڵ�����������ƽ������*/
        lc->bf=0;
        R_Rotate(p);/*��˳ʱ����ת*/
      }
      else /*�½ڵ������p������������������*/
         /*������ʱ����ת����˳ʱ����ת*/
      {
        lrc=lc->leftchild;
        if(lrc->bf==1) /*����*p�����Һ��ӵ�ƽ������*/
        {
          (*p)->bf=-1;
          lc->bf=0;
        }
        if(lrc->bf==0) /*����*p�����Һ��ӵ�ƽ������*/
        {
          (*p)->bf=0;
          lc->bf=0;
        }
        if(lrc->bf==-1) /*����*p�����Һ��ӵ�ƽ������*/
        {
          (*p)->bf=0;
          lc->bf=1;
        }
        lrc->bf=0;
        L_Rotate(&((*p)->rightchild)); /*����˳ʱ����ת*/
        R_Rotate(p); /*������ʱ����ת*/
      }
      if(flag==1) /*����������Ǹ��ڵ��ƽ��*/
      *root=*p;
      else /**parentָ����ת��Ľڵ�*p*/
      {
        if((*parent)->key<(*p)->key)
          (*parent)->rightchild=*p;
        else
          (*parent)->leftchild=*p;
      }
    }
    void BTreeinsert(bstnode **root,int kx)
    {
      bstnode *point;/*����ָ��point����ʼָ������root;*/
      bstnode *s; /*����ָ��s��ָ���½��*/
      bstnode *a;/*����ָ��a��ָ��������������ƽ�����Ӳ�����0�Ľ��*/
      bstnode *f;/*����ָ��f��ָ��a�ĸ����root;*/
      bstnode *parent;/*����ָ��parent������ָ��point���ĸ����*/
      bstnode *b;
      int d;/*���ƽ������*/
      s=(bstnode *)malloc(sizeof(bstnode));/*Ϊ�²���kx����ռ䲢��ʼ��*/
      s->key=kx;
      s->leftchild=NULL;
      s->rightchild=NULL;
      s->bf=0;
      if (*root==NULL)/*ƽ�������Ϊ��*/
      {
        *root=s;
      }
      /*ƽ���������Ϊ��*/
      else
      {
        point=*root;
        parent=NULL;
        a=*root;
        f=NULL;
        while(point!=NULL)/*��pָ���������Ϊ��*/
        {
          if(point->bf!=0)/*��sƽ�����Ӳ�Ϊ0*/
          {
            a=point;
            f=parent;
         }/*endif*/
          parent=point;
          if(point->key>s->key)/*�½��ֵС�ڵ�ǰ���point��ֵ*/
            point=point->leftchild;
          else
            point=point->rightchild;
        }
        if(s->key<parent->key)/*�½��ֵС���ҵ���ƽ�������Ҷ�ӽ��parent��ֵ��s��Ϊparent�����ӽ��*/
          parent->leftchild=s;
        else
          parent->rightchild=s;
         /*�޸Ĵ�a��s���ڵ��ƽ������*/
        if(s->key<a->key)
          point=a->leftchild;
        else
          point=a->rightchild;
        while(point!=s)  /*�޸Ĵ�a������ʼ���½ڵ�s���ڵ��ƽ������*/
        {
          if(s->key<point->key)
          {
            point->bf=1;
            point=point->leftchild;
          }
          else
          {
            point->bf=-1;
            point=point->rightchild;
          }
        }
        if(s->key<a->key)/*����½ڵ������������a�ڵ���������ϲ���*/
        {
          if(a->bf==0)    /*ԭ���������ȸ�*/
            a->bf=1;
          else if(a->bf==-1) /*ԭ��������1*/
            a->bf=0;
          else if(a->bf==1)  /*ԭ��������1*/
            LeftBalance(&f,&a,root,kx);/*������ƽ����ת*/
        }
        else
          if(s->key>a->key)/*����½ڵ������������a�ڵ���������ϲ���*/
          {
            if(a->bf==0)    /*ԭ���������ȸ�*/
              a->bf=-1;
          else if(a->bf==-1) /*ԭ��������1*/
            RightBalance(&f,&a,root,kx); /*������ƽ����ת*/
          else if(a->bf==1)  /*ԭ��������1*/
            a->bf=0;
        }
      }
    }/* BTreeinsert��������*/
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
        printf("please input the data you want to insert:(zero will exit)\n");
        scanf("%d",&kx);  /*��������ҵ�ֵkx*/
        if(kx==0) /*����ֵΪ0���������*/
          break;
        BTreeinsert(&root,kx); /*���ؼ���Ϊkxֵ���뵽ƽ���������*/
        printf("the inorder traversal of the tree is:");
        inorder(root);/*��������������������*/
        printf("\n");
      }
    }

