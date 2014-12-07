//���������

typedef int OBT_DataType;


typedef struct Node
{
	OBT_DataType data;
	struct Node* left,*right;
}OBT_Node;

typedef struct 
{
	OBT_Node* root;
	int (*rel)(OBT_DataType,OBT_DataType);
}OTree;

//�����½��
OBT_Node* OBT_makeNode(OBT_DataType value)
{
	OBT_Node* new_ptr=(OBT_Node*)malloc(sizeof(OBT_Node));
	new_ptr->data=value;
	new_ptr->left=new_ptr->right=0;
	return new_ptr;
}

//��ʼ����
void OBT_init(OTree* p_ot,int (*rel)(OBT_DataType,OBT_DataType))
{
	p_ot->root=0;
	p_ot->rel=rel;
}

void OBT_clear_help(OBT_Node** root)
{
	if(*root)
	{
		OBT_clear_help(&((*root)->left));
		OBT_clear_help(&((*root)->right));
		free(*root);
		*root=0;
	}
}
//���
void OBT_clear(OTree* p_ot)
{
	OBT_clear_help(&(p_ot->root));
}

int OBT_insert_help(OBT_Node** root,OBT_DataType value,
					int (*rel)(OBT_DataType,OBT_DataType))
{
	if(*root==0)
	{
		*root=OBT_makeNode(value);
		return 1;
	}
	if(rel(value,(*root)->data))
		return OBT_insert_help(&((*root)->left),value,rel);
	if(rel((*root)->data,value))
		return OBT_insert_help(&((*root)->right),value,rel);
	return 0;
}
//���룬����ֵ��ʾ�����Ƿ�ɹ������ظ�ֵʱʧ�ܣ�����0�����򷵻�1
int OBT_insert(OTree*p_ot,OBT_DataType value)
{
	return OBT_insert_help(&(p_ot->root),value,p_ot->rel);
}

void OBT_inPrint_help(OBT_Node* root)
{
	if(root)
	{
		OBT_inPrint_help(root->left);
		printf("%d ",root->data);
		OBT_inPrint_help(root->right);
	}	
}
void OBT_inPrint(OTree t)
{
	OBT_inPrint_help(t.root);
	printf("\n");
}

int OBT_find_help(OBT_Node* root,OBT_DataType value,int (*rel)(OBT_DataType,OBT_DataType))
{
	if(root)
	{
		if(rel(value,root->data))
			return OBT_find_help(root->left,value,rel);
		if(rel(root->data,value))
			return OBT_find_help(root->right,value,rel);
		return 1;
	}
	return 0;
}
//��ֵ���ң����򷵻�1�����򷵻�0
int OBT_find(OTree t,OBT_DataType value)
{
	return OBT_find_help(t.root,value,t.rel);
}

void OBT_remove_help(OBT_Node** root)
{
	OBT_Node** remove_ptr;
	//ɾ�����û�к���
	if((*root)->left==0&&(*root)->right==0)
	{
		free(*root);
		*root=0;
		return;
	}
	//ɾ�����ֻ������
	if((*root)->left!=0&&(*root)->right==0)
	{
		OBT_Node* del;
		del=*root;
		*root=(*root)->left;
		free(del);
		return;
	}
	//ɾ�����ֻ���Һ���
	if((*root)->left==0&&(*root)->right!=0)
	{
		OBT_Node* del;
		del=*root;
		*root=(*root)->right;
		free(del);
		return;
	}
	//ɾ�������������
	remove_ptr=&((*root)->right);
	while((*remove_ptr)->left)
		remove_ptr=&((*remove_ptr)->left);
	(*root)->data=(*remove_ptr)->data;
	OBT_remove_help(remove_ptr);
}

//��ֵɾ��������ɾ������1�����򷵻�0
int OBT_remove(OTree*p_ot,OBT_DataType value)
{
	OBT_Node** remove_ptr=&(p_ot->root);
	while((*remove_ptr))
	{
		if(p_ot->rel(value,(*remove_ptr)->data))
			remove_ptr=&((*remove_ptr)->left);
		else if(p_ot->rel((*remove_ptr)->data,value))
			remove_ptr=&((*remove_ptr)->right);
		else
		{
			OBT_remove_help(remove_ptr);
		    return 1;
		}
	}
	return 0;
}



