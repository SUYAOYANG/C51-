/**
	*���ܣ�����ָ�룬��10����������ѡ������,��С����
	*���ߣ�Yang
	*ʱ�䣺2020/1/28
	*/

#include <stdio.h>

/*������������*/
void swap(int *p1,int *p2)
{
    int temp;
    temp=*p1;
    *p1=*p2;
    *p2=temp;
}

/*ѡ�����򣬴�С����*/
void SelectionSort(int *p,int n)
{
	int i,j,k,temp;

	for(i=0;i<n-1;i++)
	{
		k=i;
		for(j=i+1;j<n;j++)
		{
			if(*(p+j)<*(p+k))
			{
				k=j;
			}
			if(k!=i)
			{
                swap(p+k,p+i);
			}
		}
	}
}

void main()
{
	int i,*p,array[10];
	p=array;

	/*��������*/
	printf("Please input 10 numbers:\n");
	for(i=0;i<10;i++)
	{
		scanf("%d",p++);
	}

	/*����*/
	p=array;
	SelectionSort(p,10);

	/*��ӡ����*/
	printf("After sort:\n");
	p=array;
	for(i=0;i<10;i++)
	{
		printf("%4d",*(p++));
	}
	printf("\n");

}
