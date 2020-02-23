/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�飬�¶ȴ�����ģ��DS18B20,������ģ�飬���������ģ�飬Һ��1602ģ��
*		�ļ����� �� DS18B20�¶ȴ������¿�ϵͳ.c
*		�汾		 �� v1.0
*		˵��		 �� ��ǰ�����������ʾ��ǰ�ɼ����Ļ����¶ȣ�0~99.9��C����
*					�¶ȵ���20��Cʱ���������������Ρ���������P1^0�ڷ����������˸��
*					�¶ȵ���18��Cʱ���������Կ조�Ρ���������P1^0��P1^1�����������������˸��
*					�¶ȸ���30��Cʱ���������������Ρ���������P1^2�ڷ����������˸��
*					�¶ȸ���32��Cʱ���������Կ조�Ρ���������P1^2��P1^3�����������������˸��
*	
*						
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-02-03	Yang			v1.0�汾���в���
*				v1.1		2020-02-03	Yang			����Һ����ʾ�Ĺ��ܣ���Һ������ʾ�����¶�ֵ
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#include <stdio.h>
#include "24c02.h"
#define uchar unsigned char
#define uint unsigned int

/****�����¶ȴ������˿�****/
sbit ds=P2^2;//�¶ȴ������ź���

/****��������ܶ˿�****/
sbit dula=P2^6;//��ѡ
sbit wela=P2^7;//λѡ

/****�����������˿�****/
sbit beep=P2^3;

/****�������������****/
sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;

/****��ʼ��Һ���˿�****/
sbit lcden=P3^4;
sbit rs=P3^5;

/****��ʼ��Һ����ʾ״̬****/
uchar code table_1[]="Temperature:";

/****�����¶���ر���****/
uint temp_int;//���͵��¶�����
float temp_float;//�����͵��¶�����
uint warn_l1=200;//�¶�����ֵ�����¶�ֵ����10��Ľ��
uint warn_l2=180;//�¶�����ֵ
uint warn_h1=300;//�¶�����ֵ
uint warn_h2=320;//�¶�����ֵ

/****�����������ʾ��ֵ****/
uchar code table[]={
	0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,			//����С�����0~9����
	0xbf,0x86,0xdb,0xcf,
	0xe6,0xed,0xfd,0x87,
	0xff,0xef			//��С�����0~9����
};

/****��ʱ��������ʱn����****/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/****Һ��д�����****/
void lcd_write_cmd(uchar cmd)
{
	rs=0;
	lcden=0;
	P0=cmd;
	delay_ms(5);
	lcden=1;
	delay_ms(5);
	lcden=0;
}

/****Һ��д���ݺ���****/
void lcd_write_data(uchar data_val)
{
	rs=1;
	lcden=0;
	P0=data_val;
	delay_ms(5);
	lcden=1;
	delay_ms(5);
	lcden=0;
}

/****Һ����ʾ����****/
void lcd_display_temp(uchar add,uint temp_int)
{
	uchar ge,shi,xiao;
	shi=temp_int/100;
	ge=temp_int%100/10;
	xiao=temp_int%100%10;
	
	lcd_write_cmd(0x80+add);//������ʾλ��
	lcd_write_data(0x30+shi);//��ȥҺ����ʾʮλ
	lcd_write_data(0x30+ge);//��ȥҺ����ʾ��λ
	lcd_write_cmd(0x80+add+3);
	lcd_write_data(0x30+xiao);//��ȥҺ����ʾС������
}

/****Һ��1602��ʼ������****/
void LcdInit()
{
	uchar i;

	/*��ʼ��Һ������*/
	wela=0;
	dula=0;//�ر�������������ˣ���ֹ��Һ����ʾ��������
	lcden=0;
	I2C_init();//��ʼ��E2PROMģ��AT24C02,�����ڴ�
	lcd_write_cmd(0x38);
	lcd_write_cmd(0x0c);
	lcd_write_cmd(0x06);
	lcd_write_cmd(0x01);

	/*д��Һ���ϵ���ʾ�ĳ�ʼ����*/
	lcd_write_cmd(0x80);//��һ�е�1����ʾ��Temperature:��
	for(i=0;i<12;i++)
	{
		lcd_write_data(table_1[i]);
		delay_ms(5);
	}

	lcd_write_cmd(0x80+14);//��һ�е�15����ʾ��.��
	lcd_write_data('.');
	delay_ms(5);
}

/****DS18B20��λ����ʼ������****/
void DsReset()
{
	uint i;
	ds=0;//����������
	i=103;
	while(i>0)i--;//��ʱ720us����
	ds=1;//����������
	i=4;
	while(i>0)i--;//��ʱ30us����
}

/****��1λ���ݺ���****/
uchar TempReadBit()
{
	uint i;
	bit data_val;
	ds=0;
	i++;//����ʱ����
	ds=1;
	i++;
	i++;
	data_val=ds;//�������߻�ȡ����
	i=8;
	while(i>0)i--;//��ʱ�𻺳�����
	return data_val;
}

/****��1���ֽ����ݺ���****/
uchar TempReadByte()
{
	uint i,j,data_val;
	data_val=0;
	for (i = 0; i < 8; ++i)
	{
		j=TempReadBit();
		data_val=(j<<7)|(data_val>>1);
	}
	return data_val;
}

/****��DS18B20дһ���ֽ����ݺ���****/
void TempWriteByte(uchar data_val)
{
	uint i,j;
	bit TempBit;
	for (i = 0; i < 8; ++i)
	{
		/*�����ȡһ���ֽڵ�λ����*/
		TempBit=data_val&0x01;
		data_val>>=1;

		/*д1*/
		if (TempBit)
		{
			ds=0;
			j++;j++;
			ds=1;
			j=8;
			while(j>0)j--;
		}

		/*д0*/
		else
		{
			ds=0;
			j=8;
			while(j>0)j--;
			ds=1;
			j++;j++;
		}
	}
}

/****DS18B20��ȡ�¶Ȳ�ת��****/
void TempChange()
{
	DsReset();
	delay_ms(1);
	TempWriteByte(0xcc);//����ROM�����Ϊֻ��һ��DS18B20����������Ҫ��ȡROM������ƥ��ROM����
	TempWriteByte(0x44);//�¶�ת������
}

/****��ȡ�Ĵ����д洢���¶�����****/
uint GetTemp()
{
	uchar LowWord,HighWord;
	DsReset();
	delay_ms(1);
	TempWriteByte(0xcc);
	TempWriteByte(0xbe);//��ȡ�ݴ�������
	LowWord=TempReadByte();//�Ͱ�λ
	HighWord=TempReadByte();//�߰�λ

	/*��ȡ�����¶�ֵ*/
	temp_int=HighWord;
	temp_int<<=8;
	temp_int=temp_int|LowWord;//�����ֽں�Ϊһ����

	/*��ȡ�������¶�ֵ*/
	temp_float=temp_int*0.0625;//�¶��ڼĴ�����Ϊ12λ���ֱ���Ϊ0.0625��
	temp_int=temp_float*10+0.5;
	temp_float=temp_float+0.05;

	return temp_int;//���������¶�ֵ
}

/****�������ʾ����****/
void display(uchar num,uchar data_val)	//numΪ�ڼ�������ܣ�data_valΪ�¶�ֵ
{
	uchar i;
	
	/*������ѡ*/
	dula=0;
	P0=table[data_val];
	dula=1;
	dula=0;
	
	/*����λѡ*/
	wela=0;
	i=0xff;//��Ӱ
	i=i&(~((0x01)<<(num)));//��i���洢λѡ���ݣ�ֻ��һλΪ0
	P0=i;
	wela=1;
	wela=0;
	delay_ms(1);
}

/****�������ʾ�¶�ֵ****/
void TempDisplay(uint temp_int)
{
	uchar i;

	/*��һ���������ʾʮλ*/
	i=temp_int/100;
	display(0,i);

	/*�ڶ����������ʾ��λ*/
	i=temp_int%100/10;
	display(1,i+10);//��С����

	/*�������������ʾС��λ*/
	i=temp_int%100%10;
	display(2,i);
}

/****����������������˸����****/
void TempWarn(uchar noice,uchar led)	//noiceΪ����������ledΪ������
{
	uchar i;
	i=noice;

	/*���� ����*/
	beep=0;//����������
	P1=~(led);//������Ӧ�ĵ���
	while(i--)
	{
		TempDisplay(GetTemp());//����ʾ�¶������������ʱ����
	}

	/*ȡ������ ����*/
	beep=1;
	P1=0xff;
	i=noice;
	while(i--)
	{
		TempDisplay(GetTemp());//����ʾ�¶������������ʱ����
	}
}

/****�¶ȴ�����****/
void TempDeal(uint temp_int)
{
	uchar i;

	/*�¶ȴﵽ����ֵ�����б�������*/
	if ((temp_int>warn_l2)&&(temp_int<=warn_l1))//�¶ȴ���18�㣬С��20��
	{
		TempWarn(40,0x01);//��һ�������������������Ρ�
	}

	else if (temp_int<=warn_l2)//�¶�С��18��
	{
		TempWarn(10,0x03);//��һ�������������������̡��Ρ�
	}

	else if ((temp_int>warn_h1)&&(temp_int<=warn_h2))//�¶ȴ���30�㣬С��32��
	{
		TempWarn(40,0x04);//�����������������������Ρ�
	}

	else if (temp_int>=warn_h2)//�¶ȴ���32��
	{
		TempWarn(10,0x0c);//�������ĸ��������������̡��Ρ�
	}

	/*�¶�δ�ﵽ����ֵ��������������������ʾ�¶�*/
	else
	{
		i=40;
		while(i--)
		{
			TempDisplay(GetTemp());
		}
	}
}

/****���ڳ�ʼ������****/
void SerialInit()
{
	TMOD=0x20;//�趨����1��������ʽ2
	PCON=0x00;
	SCON=0x50;
	TH1=0xfd;
	TL1=0xfd;//������9600
	TR1=1;//��������
}

/****�������ݷ��ͺ���****/
void SerialSendData(uchar *data_ptr)
{
	do
	{
		SBUF=*data_ptr++;
		while(!TI);//�ȴ��������
		TI=0;
	}while(*data_ptr);//����ѭ��ֱ���ַ�Ϊ'\0'
}

/****������****/
void main()
{
	uchar buff[4];
	uchar i;

	/*��ʼ��Һ��*/
	LcdInit();
	
	/*��ʼ������*/
	SerialInit();

	while(1)
	{	
		/*�¶�ת��������ܡ�Һ����ʾ�¶�*/
		TempChange();
		for (i = 0; i < 10; ++i)
		{
			lcd_display_temp(12,GetTemp());//Һ��������ܹ���P0�ڣ�����������ǰ��λ������˸������
			delay_ms(100);
			TempDisplay(GetTemp());
		}

		/*�����¶�ֵ*/
		TempDeal(temp_int);

		/*���ڷ�������*/
		sprintf(buff,"%f",temp_float);//���������¶ȸ�ʽת��Ϊ�ַ���
		for (i = 0; i < 10; ++i)
		{
			TempDisplay(GetTemp());//�¶���ʾ
		}
		SerialSendData(buff);

		/*�¶���ʾ����ʱ*/
		for (i = 0; i < 10; ++i)
		{
			TempDisplay(GetTemp());
		}
	}
	
}
