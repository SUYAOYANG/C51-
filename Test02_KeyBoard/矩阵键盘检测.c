/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢�������ģ��
*		�ļ����� �� ������̼��.c
*		�汾		 �� v1.0
*		˵��		 �� 4X4������̿����������ʾ"0~F"
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-12	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;
sbit wela=P2^7;

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

/*��ʾ�����ǰһλ*/
void display(uchar num)
{
	/*��ʾ������*/
	P0=table[num];
	dula=1;
	dula=0;
}

/*������̼��*/
void MatrixKeyScan()
{
	uchar key,temp;
	/*temp=P3Ϊɨ��P3�˿�*/
	
	/*����һ��*/
	P3=0xfe;//��һ��Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xee:
					key=0;
					break;
				
				case 0xde:
					key=1;
					break;
				
				case 0xbe:
					key=2;
					break;
				
				case 0x7e:
					key=3;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			display(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*���ڶ���*/
	P3=0xfd;//�ڶ���Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xed:
					key=4;
					break;
				
				case 0xdd:
					key=5;
					break;
				
				case 0xbd:
					key=6;
					break;
				
				case 0x7d:
					key=7;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			display(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*��������*/
	P3=0xfb;//������Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xeb:
					key=8;
					break;
				
				case 0xdb:
					key=9;
					break;
				
				case 0xbb:
					key=10;
					break;
				
				case 0x7b:
					key=11;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			display(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*��������*/
	P3=0xf7;//������Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xe7:
					key=12;
					break;
				
				case 0xd7:
					key=13;
					break;
				
				case 0xb7:
					key=14;
					break;
				
				case 0x77:
					key=15;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			display(key);//�Ȱ����ɿ�������ʾ����
		}
	}
}

/*������*/
int main()
{
	P0=0;//�ȹر�����ܵ����ж�ѡ
	dula=1;
	dula=0;
	
	P0=0xc0;//λѡ�����������
	wela=1;
	wela=0;
	while(1)
	{
		MatrixKeyScan();
	}
	return 0;
}
