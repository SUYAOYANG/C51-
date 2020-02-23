/*
***********************************************************************************************************************************************
*
*		ģ������ �� Һ��ģ��1602
*		�ļ����� �� 1602Һ����̬��ʾ.c
*		�汾		 �� v1.0
*		˵��		 �� ���в�����ʽ��ʵ����1602Һ�����ӵ�һ���Ҳ�����"I LOVE WZH,GET!"��ͬʱ�ڵڶ����Ҳ�����"WWW.SYY.COM"
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-14	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
	
sbit LCD_EN=P3^4;
sbit LCD_RS=P3^5;
sbit dula=P2^6;
sbit wela=P2^7;

uchar code str1[]="I LOVE WZH!";
uchar code str2[]="LOVE YOU,BABY!";
uchar count;

/*��ʱ��������ʱn����*/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/*д�����*/
void LCD_write_cmd(uchar cmd_val)
{
	LCD_RS=0;//ѡ��д����
	P0=cmd_val;//��Ҫд���������͵�����������
	delay_ms(5);//������ʱ�Դ������ȶ�
	LCD_EN=1;//ʹ�ܶ˸�һ�����壬��Ϊ��ʼ�������Ѿ���LCD_EN=0
	delay_ms(5);//������ʱ
	LCD_EN=0;//��ʹ�ܶ����㣬��ɸ�����
}

/*д���ݺ���*/
void LCD_write_data(uchar data_val)
{
	LCD_RS=1;//ѡ��д����
	P0=data_val;//��Ҫд�������͵�����������
	delay_ms(5);//������ʱ�Դ������ȶ�
	LCD_EN=1;//ʹ�ܶ˸�һ�����壬��Ϊ��ʼ�������Ѿ���LCD_EN=0
	delay_ms(5);//������ʱ
	LCD_EN=0;//��ʹ�ܶ����㣬��ɸ�����
}

/*��ʼ��LCD*/
void Init()
{
	dula=0;
	wela=0;//�رն�ѡ��λѡ
	LCD_EN=0;//�ȹر�Һ��ʹ�ܶ�
	LCD_write_cmd(0x38);//����16 X 2��ʾ��5 X 7����8λ���ݽӿ�
	LCD_write_cmd(0x0c);//����ʾ������ʾ��꣬����˸
	LCD_write_cmd(0x06);//дһ���ַ���ָ���1
	LCD_write_cmd(0x01);//��ʾ��0������ָ����0
}

void main()
{
	/*��ʼ��LCD*/
	Init();
	
	/*��д��һ�е�����ָ�룬��д���һ������*/
	LCD_write_cmd(0x80+0x10);//������д�����ʾ�����ַ��
	
	for(count=0;count<11;count++)
	{
		LCD_write_data(str1[count]);
		delay_ms(5);
	}
	
	/*��д�ڶ��е�����ָ�룬��д��ڶ�������*/
	LCD_write_cmd(0x80+0x50);
	
	for(count=0;count<14;count++)
	{
		LCD_write_data(str2[count]);
		delay_ms(5);
	}
	
	for(count=0;count<16;count++)
	{
		LCD_write_cmd(0x18);//����Ļ���ƣ�����������Ҫ��ʾ������
		delay_ms(200);//���200ms����һ����ַ
	}
	while(1);
}
