/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢ADת��ģ�顢����ģ��
*		�ļ����� �� ���ڴ�ӡADת��ֵ.c
*		�汾		 �� v1.0
*		˵��		 �� ��λ�����Ƶ�Ƭ������ADת����������ܵ�ǰ��λ��ʮ���ƶ�̬��ʾ��A/Dת������������ͬʱ����λ���������ֵ��ӡ����
*							 ��8λ������A/Dת��������Ӧʮ����0~255��
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-13	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;//����������U1�������
sbit wela=P2^7;//����������U2�������
sbit adwr=P3^6;//����ADת������д���
sbit adrd=P3^7;//����ADת�����Ķ�ȡ��

uchar FlagTime,FlagUart,FlagOn,ADval,T0_Time;
float ADo;

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

/*��ʾ����ܺ���λ*/
void display(uchar num)
{
	uchar ge,shi,bai;
	ge=num%10;
	shi=num%100/10;
	bai=num/100;
	
	/*��ʾ��λ*/
	wela=1;
	P0=0x7e;
	wela=0;
	dula=1;
	P0=table[ge];
	dula=0;
	delay_ms(5);
	
	/*��ʾʮλ*/
	wela=1;
	P0=0x7d;
	wela=0;
	dula=1;
	P0=table[shi];
	dula=0;
	delay_ms(5);
	
	/*��ʾ��λ*/
	wela=1;
	P0=0x7b;
	wela=0;
	dula=1;
	P0=table[bai];
	dula=0;
	delay_ms(5);
	
}

/*��ʼ������*/
void Init()
{
	/*��ʱ��0Ϊ������ʽ1����ʱ��1Ϊ������ʽ2*/
	TMOD=0x21;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=0xfd;
	TL1=0xfd;
	ET0=1;
	TR1=1;
	
	/*����Ϊ������ʽ1*/
	SCON=0x50;//�ȵ����ԼĴ�����λ��ʼ�������գ���Ϊ������λʱ��Ҫע��˳��SM0=0,SM1=1,REN=1,������������ȶ�
	
	/*�����ж�*/
	EA=1;
	ES=1;

}

/*����ADת������ȡ��ֵ*/
uchar GetAD()
{
	uchar ad_val;
	/*ADת��*/
	adwr=1;
	_nop_();
	adwr=0;
	_nop_();
	adwr=1;
	
	P1=0xff;
	
	/*��ȡת��ֵ*/
	adrd=1;
	_nop_();
	adrd=0;
	_nop_();
	ad_val=P1;
	adrd=1;
	
	return ad_val;
}

/*������*/
int main()
{
	/*��ʼ��*/
	Init();
	
	/*ADת��������U2�洢����������λΪ��*/
	wela=1;
	P0=0x7f;
	wela=0;
	
	while(1)
	{
		/*���ڽ�����ϣ��жϽ��յ�����*/
		if(FlagUart==1)
		{
			FlagUart=0;
			ES=0;
			TI=1;
			switch(FlagOn)
			{
				case 0:
					puts("Turn on AD!\n");
					TR0=1;
					break;
				
				case 1:
					printf("Turn off AD��\n");
					TR0=0;
					break;
				
				case 2:
					printf("Error!\n");
					break;
			}
			while(!TI);
			TI=0;
			ES=1;
		}
		
		/*���1s����ADת��ֵ*/
		if(FlagTime==1)
		{
			FlagTime=0;
			ADval=GetAD();
			ADo=(float)ADval*5.0/256.0;
			ES=0;
			TI=1;
			printf("The voltage is %fV\n",ADo);
			while(!TI);
			TI=0;
			ES=1;
		}
		
		/*�������ʾADת��ֵ*/
		display(ADval);
		
	}
	
	return 0;
}

/*��ʱ��0�жϷ�����*/
void T0_time() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	T0_Time++;
	if(T0_Time==20)//��1s
	{
		T0_Time=0;
		FlagTime=1;
	}

}

/*�����жϷ�����*/
void Ser_RxMsg() interrupt 4
{
	uchar temp;
	temp=SBUF;
	RI=0;
	FlagUart=1;
	if(temp==0)
		FlagOn=0;
	else if(temp==1)
		FlagOn=1;
	else
		FlagOn=2;
}