//˫������
typedef int DLL_DataType;

typedef struct Node
{
	DLL_DataType data;
	struct Node* pre,*next;
}DLL_Node;

typedef struct 
{
	DLL_Node* head,*tail;
}DList;

//�����½��
DLL_Node* DLL_makeNode(DLL_DataType value)
{
	DLL_Node* new_ptr=(DLL_Node*)malloc(sizeof(DLL_Node));
	new_ptr->data=value;
	new_ptr->pre=new_ptr->next=0;
	return new_ptr;
}

//��ʼ��������
void DLL_init(DList* p_dl)
{
	p_dl->head=p_dl->tail=0;
}


//���
void DLL_clear(DList* p_dl)
{
	while(p_dl->head)
	{
		DLL_Node* del_ptr=p_dl->head;
		p_dl->head=p_dl->head->next;
		free(del_ptr);
	}
	p_dl->tail=0;
}

//�����Ƿ��
int DLL_isEmpty(DList dl)
{
	return dl.head==0;
}

//������ͷ������
void DLL_insertAtHead(DList* p_dl,DLL_DataType value)
{
	DLL_Node* new_ptr=DLL_makeNode(value);
	new_ptr->next=p_dl->head;
	if(p_dl->head)
		p_dl->head->pre=new_ptr;
	p_dl->head=new_ptr;
	if(p_dl->tail==0)
		p_dl->tail=new_ptr;
}

//������β������
void DLL_insertAtTail(DList* p_dl,DLL_DataType value)
{
	DLL_Node* new_ptr=DLL_makeNode(value);
	new_ptr->pre=p_dl->tail;
	if(p_dl->tail)
		p_dl->tail->next=new_ptr;
	p_dl->tail=new_ptr;
	if(p_dl->head==0)
		p_dl->head=new_ptr;
}

//������ͷ��ɾ��������ֵ��ʾɾ���Ƿ�ɹ�
int DLL_deleteFromHead(DList* p_dl,DLL_DataType* p_value)
{
    DLL_Node* del_ptr=p_dl->head;
	if(del_ptr==0)
		return 0;
	*p_value=del_ptr->data;	
	p_dl->head=del_ptr->next;
	if(p_dl->head)
		p_dl->head->pre=0;
	else
		p_dl->tail=0;
	free(del_ptr);
	return 1;
}

//������β��ɾ��������ֵ��ʾɾ���Ƿ�ɹ�
int DLL_deleteFromTail(DList* p_dl,DLL_DataType* p_value)
{
    DLL_Node* del_ptr=p_dl->tail;
	if(del_ptr==0)
		return 0;
	*p_value=del_ptr->data;	
	p_dl->tail=del_ptr->pre;
	if(p_dl->tail)
		p_dl->tail->next=0;
	else
		p_dl->head=0;
	free(del_ptr);
	return 1;
}


