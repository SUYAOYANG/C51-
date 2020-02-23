/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ��,E2PROMģ��
*		�ļ����� �� STC��Ƭ��E2PROMӦ��.c
*		�汾		 �� v1.0
*		˵��		 ������STC��Ƭ���Դ���E2PROM���洢һ�鰴���������λ���ݣ����������������ʾ������ÿ��ʾһ�ξ�д��һ��
*							 ���ر�ʵ����Դ�ٿ���ʱ����E2PROM��ȡ���ݲ���ʾ���������
*	
*						
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-31	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

/****����ISP�Ĳ�������****/
#define RdCommand 0x01//������
#define PrgCommand 0x02//�������
#define EraseCommand 0x03//��д����

/****���峣��ָʾ****/
#define Error 1
#define Ok 0
#define WaitTime 0x01//����CPU�ĵȴ�ʱ��

/****����ISP��ؼĴ���****/
sfr  ISP_DATA=0xe2;
sfr  ISP_ADDRH=0xe3;
sfr  ISP_ADDRL=0xe4;
sfr  ISP_CMD=0xe5;
sfr  ISP_TRIG=0xe6;
sfr  ISP_CONTR=0xe7;

/****�����������ز���****/
sbit dula=P2^6;
sbit wela=P2^7;
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

uchar num_ms;

/****��ʱ��������ʱn����****/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/****��ʾ�����ǰ��λ****/
void display(uchar ge,uchar shi)
{
	/*��ʾ��λ*/
	wela=1;
	P0=0xdf;
	wela=0;
	dula=1;
	P0=table[ge];
	dula=0;
	delay_ms(5);
	
	/*��ʾʮλ*/
	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[shi];
	dula=0;
	delay_ms(5);	
}

/****��ISP,IAP����****/
void ISP_IAP_enable()
{
	EA=0;//���ж�
	ISP_CONTR=ISP_CONTR&0x18;//�������ⲽ����̫�����ⲽ����˼
	ISP_CONTR=ISP_CONTR|WaitTime;
	ISP_CONTR=0x80;//ISPEN=1
}

/****�ر�ISP,IAP����****/
void ISP_IAP_disable()
{
	ISP_CONTR=0x00;//ISPEN=0
	ISP_TRIG=0x00;
	EA=1;//���ж�
}

/****���ú���****/
void ISP_public()
{
	ISP_IAP_enable();
	ISP_TRIG=0x46;//����ISP_IAP�����ֽ�1
	ISP_TRIG=0xb9;//����ISP_IAP�����ֽ�2
	_nop_();
}

/****�ֽڶ�ȡ****/
uchar byte_read(uint byte_addr)
{
	ISP_ADDRH=(uchar)(byte_addr>>8);//�����ַ��8λ
	ISP_ADDRL=(uchar)(byte_addr&0x00ff);//�����ַ�ĵ�8λ
	ISP_CMD=ISP_CMD&0xf8;//�����3λ
	ISP_CMD=ISP_CMD|RdCommand;//д�������
	ISP_public();//ִ������
	ISP_IAP_disable();
	return ISP_DATA;
}

/****��������****/
void SectorErase(uint sector_addr)
{
	uint iSectorAddr;
	iSectorAddr=sector_addr&0xfe00;//ȡ������ַ
	ISP_ADDRH=(uchar)(iSectorAddr>>8);//�����ַ��8λ
	ISP_ADDRL=0x00;//�����ַ�ĵ�8λ
	ISP_CMD=ISP_CMD&0xf8;//�����3λ
	ISP_CMD=ISP_CMD|EraseCommand;//д���������
	ISP_public();//ִ������
	ISP_IAP_disable();
}

/****�ֽ�д****/
void byte_write(uint byte_addr,uchar byte_data)
{
	ISP_ADDRH=(uchar)(byte_addr>>8);//�����ַ��8λ
	ISP_ADDRL=(uchar)(byte_addr&0x00ff);//�����ַ�ĵ�8λ
	ISP_CMD=ISP_CMD&0xf8;//�����3λ
	ISP_CMD=ISP_CMD|PrgCommand;//д���ֽ�д����
	ISP_DATA=byte_data;//д������
	ISP_public();//ִ������
	ISP_IAP_disable();
}

/****������****/
void main()
{
	uchar num_s;
	
	/*������ʱ��0����Ϊ������ʽ1*/
	TMOD=0x01;
	TH0=(65536-50000)/256;//װ��ֵ��50msһ��
	TL0=(65536-50000)%256;
	TR0=1;
	
	/*�����ж�*/
	EA=1;//���ж�
	ET0=1;//��ʱ��0�ж�
	
	/*����ʼʱ����E2PROM��ȡ����*/
	num_s=byte_read(0x2000);
	
	if(num_s>=60)//��ֹ�״��ϵ��ȡ����
		num_s=0;
	while(1)
	{
		if(num_ms>=20)
		{
			num_ms=0;
			num_s++;
			SectorErase(0x2000);//��������
			byte_write(0x2000,num_s);//��E2PROMд������
			if(num_s==60)
			{
				num_s=0;
			}
		}
		display(num_s%10,num_s/10);
	}
}

/****��ʱ��0�жϷ�����****/
void T0_time() interrupt 1
{
	TH0=(65536-50000)/256;//װ��ֵ��50msһ��
	TL0=(65536-50000)%256;
	num_ms++;
}