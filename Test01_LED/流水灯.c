/*
*************************************************************
*
*		ģ������ �� ��ˮ��ģ��
*		�ļ����� �� ��ˮ��.c
*		�汾		 �� v1.0
*		˵��		 �� ѭ�����ε���1��3��5��7����Ϊ��ˮ��
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-10	Yang			v1.0�汾���в���
*
*************************************************************
*/

#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char

//��ʱn����
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
			for(j=110;j>0;j--);
}

int main()
{	
	uchar led=0xfe;
	while(1)
	{
		P1=led;
		delay_ms(500);
		led=_crol_(led,2);//��led����ѭ���ƶ�2λ
						//C51�⺯����ѭ�����ƺ���_crol_,ѭ�����ƺ���_cror_
	}
	return 0;
}