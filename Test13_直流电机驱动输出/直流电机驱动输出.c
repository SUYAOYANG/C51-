/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢��������ģ��
*		�ļ����� �� ֱ������������.c
*		�汾		 �� v1.0
*		˵��		 �� ��������ֱ�������PWM�ź������S2���¼��٣�S3���¼���
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-02-11	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;
sbit wela=P2^7;
sbit Machine=P1^7;
sbit KEY_S2_AddSpeed=P3^4;//���ٰ���
sbit KEY_S3_SubSpeed=P3^5;//���ٰ���

uint num,Num_Show,Num_High,Num_Low;

uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

/*��ʱ��������ʱn����*/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/*��ʾ�����ǰ��λ*/
void display(uint Num)
{
	/*��ʾ��λ*/
	dula=0;
	P0=table[0];
	dula=0;
	dula=1;
	P0=0xdf;
	wela=0;
	wela=1;
	delay_ms(5);
	
	/*��ʾʮλ*/
	dula=0;
	P0=table[0];
	dula=0;
	dula=1;
	P0=0xdf;
	wela=0;
	wela=1;
	delay_ms(5);
	
	/*��ʾ��λ*/
	dula=0;
	P0=table[0];
	dula=0;
	dula=1;
	P0=0xdf;
	wela=0;
	wela=1;
	delay_ms(5);
	
	/*��ʾǧλ*/
	dula=0;
	P0=table[Num_Show];
	dula=0;
	dula=1;
	P0=0xdf;
	wela=0;
	wela=1;
	delay_ms(5);
		
}

/*ɨ�谴������*/
void KeyScan()
{
	/*�����ٰ����Ƿ���*/
	if (KEY_S2_AddSpeed==0)
	{
		delay_ms(5);//��ʱ����
		if (KEY_S2_AddSpeed==0)
		{
			num++;
			/*������ٳ����������3*/
			if (num==4)
			{
				num=3;
			}
			while(KEY_S2_AddSpeed==0);
		}
	}

	/*�����ٰ����ͷŰ���*/
	if (KEY_S3_SubSpeed==0)
	{
		delay_ms(5);//��ʱ����
		if (KEY_S3_SubSpeed==0)
		{
			if (num!=0)
			{
				num--;
			}

			else
				num=0;
			while(KEY_S3_SubSpeed==0);
		}
	}
}

/*�����ٶȱ�־�������ݴ���*/
void DisposeSpeed()
{
	switch(num)
	{
		case 0:
				Num_Show=1;
				Num_High=1;
				Num_Show=3;

		case 1:
				Num_Show=2;
				Num_High=2;
				Num_Show=2;

		case 2:
				Num_Show=3;
				Num_High=3;
				Num_Show=1;

		case 3:
				Num_Show=4;
				Num_High=4;
				Num_Show=0;
	}
}


/*����ֱ�����*/
void DriveMachine()
{
	uchar i;

	/*PWM����͵�ƽ*/
	if (Num_Show!=0)
	{
		for (int i = 0; i < Num_Low; ++i)
		{
			Machine=0;	
			display();
		}
	}

	/*PWM����ߵ�ƽ*/
	for (int i = 0; i < Num_High; ++i)
	{
		Machine=1;
		display();
	}
}


/*������*/
void main()
{
	while(1)
	{
		Machine=0;
		KeyScan();
		DisposeSpeed();
		DriveMachine();
	}
}