/**
	*���ܣ������ά����Ԫ�ص�ֵ
	*���ߣ�Yang
	*ʱ�䣺2020/1/28
	*/

#include <stdio.h>

void main()
{
	static int array[3][4]={{2,3,4,5},{1,3,5,7},{8,9,10,11}};
	int (*ptr)[4];//��ά�����ָ�����
	ptr=array;

	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			printf("%4d",*(*(ptr+i)+j));
		}
		printf("\n");
	}
}
