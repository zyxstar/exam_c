#include<stdio.h>
#include<malloc.h>
#include"queue.h"
#include"mGraph.h"

//������ɹ�����1��ʧ�ܷ���0
int MG_insertEW(MGraph* p_mg,G_Datatype v1,G_Datatype v2,unsigned w)
{
	unsigned i,j;
	for(i=0;i<p_mg->count&&p_mg->d_ptr[i]!=v1;i++);
	if(i==p_mg->count)
		return 0;
	for(j=0;j<p_mg->count&&p_mg->d_ptr[j]!=v2;j++);
	if(j==p_mg->count)
		return 0;
	if(i==j)
		return 0;
	p_mg->m_ptr[i][j]=p_mg->m_ptr[j][i]=w;
	return 1;
}




void print_minPath(MGraph mg,G_Datatype start)
{
	unsigned s;
	unsigned i,j,k;
	unsigned min,old_min;
	unsigned** arr;

	int *set;
	for(s=0;s<mg.count&&mg.d_ptr[s]!=start;s++);
	if(s==mg.count)
		return ;
	
    set=(int*)malloc(sizeof(int)*mg.count);
	for(i=0;i<mg.count;++i)
		set[i]=0;
	//�����ά���飬����ĵ�i�б���ӽ��s�����i�����·������0�б�ʾ���ɽ���������1�б�ʾ��̣��������,��ʾ;���Ľ�㡣
	arr=(unsigned**) malloc(sizeof(unsigned*)*mg.count);
	for(i=0;i<mg.count;++i)
		arr[i]=(unsigned*)malloc(sizeof(unsigned)*mg.count);
	for(i=0;i<mg.count;++i)
		arr[i][0]=arr[i][1]=0;
    old_min=s;
	set[s]=1;
	while(1)
	{	
		for(i=0;i<mg.count&&set[i];i++);
		if(i==mg.count) break;
		min=s;
		for(i=0;i<mg.count;i++)
		{
			if(set[i])
				continue;
			
			    if(mg.m_ptr[old_min][i]&&(arr[i][1]==0||mg.m_ptr[i][old_min]+arr[old_min][1]<arr[i][1]))
				{
				    arr[i][1]=mg.m_ptr[old_min][i]+arr[old_min][1];
				    if(old_min!=s)
					{

				       for(k=0;k<arr[old_min][0];k++)
						   arr[i][2+k]=arr[old_min][2+k];
					   arr[i][2+k]=old_min;
					   arr[i][0]=arr[old_min][0]+1;
					}
				}
		
			if(arr[i][1]!=0&&(min==s||arr[i][1]<arr[min][1]))
				min=i;		
		}
		if(min==s) break;	
		set[min]=1;
		old_min=min;
	}
	for(i=0;i<mg.count;i++)
	  if(i!=s)
	    if(arr[i][1])
		  {
		      printf("%c->",mg.d_ptr[s]);
		      for(j=0;j<arr[i][0];j++)
		          printf("%c->",mg.d_ptr[arr[i][2+j]]);
		      printf("%c,���%d\n",mg.d_ptr[i],arr[i][1]);
		  }
		else
			printf("%c��%cû��ͨ·\n",mg.d_ptr[s],mg.d_ptr[i]);
	  
	for(i=0;i<mg.count;i++)
		free(arr[i]);
	free(arr);
	free(set);

}
int main()
{
	int i;
	MGraph mg;
	MG_init(&mg,10);
	for(i=0;i<10;i++)
		MG_insertV(&mg,'A'+i);
	MG_insertEW(&mg,'A','B',1);
	MG_insertEW(&mg,'A','C',20);
	MG_insertEW(&mg,'A','D',3);
	MG_insertEW(&mg,'B','D',8);
	MG_insertEW(&mg,'C','E',15);
	MG_insertEW(&mg,'C','F',2);
	MG_insertEW(&mg,'E','F',5);
	MG_insertEW(&mg,'B','E',12);

	MG_insertEW(&mg,'G','H',4);
	MG_insertEW(&mg,'G','I',70);
	MG_insertEW(&mg,'G','J',12);
	MG_insertEW(&mg,'H','I',3);
	MG_insertEW(&mg,'I','J',6);

	print_minPath(mg,'F');

    printf("\n");
	print_minPath(mg,'I');




	MG_clear(&mg);

	return 0;
}