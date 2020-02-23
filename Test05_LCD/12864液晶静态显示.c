/*
***********************************************************************************************************************************************
*
*		ģ������ �� Һ��ģ��12864
*		�ļ����� �� 12864Һ����̬��ʾ.c
*		�汾		 �� v1.0
*		˵��		 �� ���в�����ʽ��ʵ����12864Һ���ĵ�һ����ʾ��0123456789����������ÿһλ��������仯��
*								�ڶ�����ʾ���Ұ�ɵ��!��,��������ʾ��www.syy.com��,�����ж�Ӧ��������ʾ���»���
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-15	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#include <stdlib.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

/*�˿ڶ���*/
#define LCD_data=P0;//���ݿ�
sbit LCD_EN=P3^4;//Һ��ʹ�ܿ���
sbit LCD_RS=P3^5;//�Ĵ���ѡ�����룬0Ϊ����ָ�1Ϊ������ʾ����
sbit LCD_RW=P3^6;//Һ����/д����
sbit LCD_PSB=P3^7;//��/���з�ʽ���ƣ�0Ϊ���У�1Ϊ����

uchar str1[10];
uchar code str2[]="�Ұ�ɵ��";
uchar code str3[]={"www.syy.com"};
uchar code str4[]={"------------"};

/*��ʱ��������ʱn����*/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/*����ָ�����ݵ�LCD*/
/*LCD_RS=L,LCD_RW=L,LCD_EN=�����壬D0-D7=ָ����*/
void LCD_write_cmd(uchar cmd_val)
{
	LCD_RS=0;
	LCD_RW=0;
	LCD_EN=0;
	P0=cmd_val;//��ָ�������͵���������
	delay_ms(5);
	LCD_EN=1;
	delay_ms(5);
	LCD_EN=0;
}

/*������ʾ���ݵ�LCD*/
/*LCD_RS=H,LCD_RW=L,LCD_EN=�����壬D0-D7=ָ����*/
void LCD_write_data(uchar data_val)
{
	LCD_RS=1;
	LCD_RW=0;
	LCD_EN=0;
	P0=data_val;//��ָ�������͵���������
	delay_ms(5);
	LCD_EN=1;
	delay_ms(5);
	LCD_EN=0;
}

/*ȷ����ʾ����*/
void LCD_SetPos(uchar x,uchar y)
{
	uchar pos;
	if(x==0)
		x=0x80;
	else if(x==1)
		x=0x90;
	else if(x==2)
		x=0x88;
	else if(x==3)
		x=0x98;
	pos=x+y;
	
	LCD_write_cmd(pos);
}

/*�����������*/
void LCD_MakeRand()
{
	uchar num;
	num=rand();
	/*���ɸ���λ*/
	str1[0]=num/10000+0x30;
	str1[1]=num%10000/1000+0x30;
	str1[2]=num%1000/100+0x30;
	str1[3]=num%100/10+0x30;
	str1[4]=num%10+0x30;
	
	num=rand();
	/*���ɵ���λ*/
	str1[5]=num/10000+0x30;
	str1[6]=num%10000/1000+0x30;
	str1[7]=num%1000/100+0x30;
	str1[8]=num%100/10+0x30;
	str1[9]=num%10+0x30;
}

/*��ʼ��Һ������*/
void LCD_Init()
{
	LCD_PSB=1;//ѡ���в���
	LCD_write_cmd(0x30);
	delay_ms(5);
	LCD_write_cmd(0x0c);
	delay_ms(5);
	LCD_write_cmd(0x01);
	delay_ms(5);
}

/*������*/
void main()
{
	uchar i;
	delay_ms(5);
	LCD_Init();
	
	/*������ʾλ��Ϊ�ڶ��еĵ�1���ַ�*/
	LCD_SetPos(1,0);
	i=0;
	while(str2[i]!='\0')
	{
		LCD_write_data(str2[i]);//��ʾ�ַ�
		i++;
	}
	
	/*������ʾλ��Ϊ�����еĵ�1���ַ�*/
	LCD_SetPos(2,0);
	i=0;
	while(str3[i]!='\0')
	{
		LCD_write_data(str3[i]);//��ʾ�ַ�
		i++;
	}
	
	/*������ʾλ��Ϊ�����еĵ�1���ַ�*/
	LCD_SetPos(3,0);
	i=0;
	while(str4[i]!='\0')
	{
		LCD_write_data(str4[i]);//��ʾ�ַ�
		i++;
	}
	
	/*������ʾλ��Ϊ��һ�еĵ�1���ַ�*/
	while(1)
	{
		LCD_SetPos(0,0);
		i=0;
		LCD_MakeRand();
		for(i=0;i<10;i++)
		{
			LCD_write_data(str1[i]);
		}
	}
}