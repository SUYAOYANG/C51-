/*
***********************************************************************************************************************************************
*
*		ģ������ �� Һ��ģ��12232
*		�ļ����� �� 12232Һ����̬��ʾ.c
*		�汾		 �� v1.0
*		˵��		 �� ���в�����ʽ��ʵ����12232Һ�����ӵ�һ���Ҳ�����"I LOVE WZH,GET!"��ͬʱ�ڵڶ����Ҳ�����"�Ұ�ɵ��"
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-15	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
	
sbit LCD_CS=P1^0;
sbit LCD_SID=P1^1;
sbit LCD_SCLK=P1^2;

uchar code str1[]="I LOVE WZH��GET!";
uchar code str2[]="�Ұ�ɵ��";
uchar count;

/*��ʱ��������ʱn����*/
void delay_ms(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/*��������*/
void LCD_send_cmd(uchar cmd_val)
{
	uchar i;
	uchar temp_data;
	
	/******�����������������һ������ָ����������Ƿ���8λ����*****/
	/*��һ�������͡�д�����ָ��*/
	temp_data=0xf8;
	LCD_CS=1;
	LCD_SCLK=0;
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	/*�ڶ���������8λָ������*/
	temp_data=cmd_val;
	temp_data&=0xf0;//ȡ����λ
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	/*������������8λָ������*/
	temp_data=cmd_val;
	temp_data=temp_data<<4;//ȡ����λ
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	LCD_CS=0;
	delay_ms(10);
}

/*�����ַ�������*/
void LCD_send_data(uchar data_val)
{
	uchar i;
	uchar temp_data;
	
	/******�����ַ������ݷ���������һ������ָ����������Ƿ���8λ����*****/
	/*��һ�������͡�д���ݡ���ָ��*/
	temp_data=0xfa;
	LCD_CS=1;
	LCD_SCLK=0;
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	/*�ڶ���������8λ�ַ�������*/
	temp_data=data_val;
	temp_data&=0xf0;//ȡ����λ
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	/*������������8λ�ַ�������*/
	temp_data=data_val;
	temp_data=temp_data<<4;//ȡ����λ
	for(i=0;i<8;i++)
	{
		temp_data=(bit)temp_data&0x80;//ȡ�����λ
		LCD_SCLK=1;
		LCD_SCLK=0;
		temp_data=temp_data<<1;
	}
	
	LCD_CS=0;
	delay_ms(10);
}

/*��ʼ��12232Һ��*/
void Init()
{
	delay_ms(100);
	LCD_send_cmd(0x30);//����8λ���ݽӿڣ�����ָ��ģʽ
	LCD_send_cmd(0x02);//��DDRAM
	LCD_send_cmd(0x06);//�α꼰��ʾ����һλ
	LCD_send_cmd(0x0c);//������ʾ�����α�أ����׹�
	LCD_send_cmd(0x30);//д��ո�����Ļ
	LCD_send_cmd(0x30);//�趨�״���ʾλ��

}

/*��ʾ�ַ���str1*/
void display_str1(uchar pos)
{
	uchar count;
	LCD_send_cmd(0x88-pos);
	for(count=0;count<15;count++)
	{
		LCD_send_data(str1[count]);
	}

}

/*��ʾ�ַ���str2*/
void display_str2(uchar pos)
{
	uchar count;
	LCD_send_cmd(0x98-pos);
	for(count=0;count<15;count++)
	{
		LCD_send_data(str2[count]);
	}

}

void main()
{
	uchar position;
	Init();
	for(position=0;position<9;position++)//����12232Һ��û��ר�ŵ�����ָ����ʹ��forѭ����ʵ������Ч����															//ʵ�������ظ���ͬ�ĵط�д����ʾ�ַ���ʵ������Ч��
	{																		//ʵ�������ظ���ͬ�ĵط�д����ʾ�ַ�
		display_str1(position);
		display_str2(position);
	}
	while(1);

}