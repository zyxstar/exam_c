//������Ϊ�����۰���ң��������������Ѿ��ź�����
#include<stdio.h>
typedef int DataType;
//��ϵ���������ڱȽ�
int less(DataType a,DataType b)
{
	return a<b;
}
//���ҳɹ�����1�����򷵻�0
int binary_search(DataType *arr,int len,DataType value,int(* comp)(DataType,DataType))
{
	int low=0;
	int high=len-1;
	int mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(comp(value,arr[mid]))
			high=mid-1;
		else if(comp(arr[mid],value))
			low=mid+1;
		else
			return 1;
	}
	return 0;
}
//�ݹ�ⷨ
int binary_search1(DataType *arr,int len,DataType value,int(* comp)(DataType,DataType))
{
	if(len<=0) 
		return 0;
	if(comp(value,arr[(len-1)/2]))
		return binary_search1(arr,(len-1)/2,value,comp);
	if(comp(arr[(len-1)/2],value))
		return binary_search1(arr+(len-1)/2+1,len-1-(len-1)/2,value,comp);
	return 1;
	
}

int main()
{
	DataType arr[10]={0,2,4,6,8,10,12,14,16,18};

    printf("%d\n",binary_search(arr,10,0,less));
	printf("%d\n",binary_search(arr,10,10,less));
	printf("%d\n",binary_search(arr,10,16,less));
	printf("%d\n",binary_search(arr,10,11,less));
    printf("\n");

	printf("%d\n",binary_search1(arr,10,0,less));
	printf("%d\n",binary_search1(arr,10,10,less));
	printf("%d\n",binary_search1(arr,10,16,less));
	printf("%d\n",binary_search1(arr,10,11,less));
	return 0;
}