/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢��������ģ��
*		�ļ����� �� �����������.c
*		�汾		 �� v1.0
*		˵��		 �� ������������ܵ���ʾ��S2ʹ���ּ�һ��S3ʹ���ּ�һ��S4ʹ���ָ�λ��S5���ƶ�ʱ���Զ���ʾ����
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-11	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;
sbit wela=P2^7;
sbit KEY_S2=P3^4;
sbit KEY_S3=P3^5;
sbit KEY_S4=P3^6;
sbit KEY_S5=P3^7;
uint ge,shi;
uint NumTotal,NumT0;

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
	ge=Num%10;
	wela=1;
	P0=0xdf;
	wela=0;
	dula=1;
	P0=table[ge];
	dula=0;
	delay_ms(5);
	
	/*��ʾʮλ*/
	shi=Num/10;
	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[shi];
	dula=0;
	delay_ms(5);
	
}

/*��ʼ����ʱ��0��������ʽ1��16λ��ʱ��*/
void Init()
{
	TMOD=0x01;
	/*װ��ֵ��50ms*/
	TH0=(65536-48572)/256;
	TL0=(65536-48572)%256;
	EA=1;
	ET0=1;
}


/*��ʱ��0�жϺ���*/
void T0_Time() interrupt 1
{
	/*װ��ֵ��50ms*/
	TH0=(65536-48572)/256;
	TL0=(65536-48572)%256;
	
	NumT0++;
	if(NumT0==20)//��1s
	{
		NumT0=0;
		NumTotal++;
		if(NumTotal==60) NumTotal=0;
	}
}

/*ɨ���������*/
void KeyScan()
{
	if(KEY_S2==0)
	{
		delay_ms(10);
		if(KEY_S2==0)
		{
			NumTotal++;
			if(NumTotal==60) NumTotal=0;
			while(!KEY_S2);//�ȴ������ɿ�
		}
	}
	
	if(KEY_S3==0)
	{
		delay_ms(10);
		if(KEY_S3==0)
		{
			if(NumTotal==0) NumTotal=60;
			NumTotal--;
			while(!KEY_S3);
		}
	}
	
	if(KEY_S4==0)
	{
		delay_ms(10);
		if(KEY_S4==0)
		{
			NumTotal=0;
			while(!KEY_S4);
		}
	}
	
	if(KEY_S5==0)
	{
		delay_ms(10);
		if(KEY_S5==0)
		{
			while(!KEY_S5);
			TR0=~TR0;
		}
	}
}

int main()
{
	Init();
	
	while(1)
	{
		KeyScan();
		display(NumTotal);
	}
	return 0;
}