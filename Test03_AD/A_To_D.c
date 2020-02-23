/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢ADת��ģ��
*		�ļ����� �� A_To_D.c
*		�汾		 �� v1.0
*		˵��		 �� ��Ƭ������ADC0804����ģʽת����������ܵ�ǰ��λ��ʮ���ƶ�̬��ʾ��A/Dת����������
*							 ��8λ������A/Dת��������Ӧʮ����0~255��
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-12	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;//����������U1�������
sbit wela=P2^7;//����������U2�������
sbit adwr=P3^6;//����ADת������д���
sbit adrd=P3^7;//����ADת�����Ķ�ȡ��
uchar ge,shi,bai;

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
void display(uchar ge,shi,bai)
{
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

/*����A/Dת�����������������ʾ�����*/
int main()
{
	uchar ADval,A1,A2,A3;//A1 A2 A3Ϊģ��������λ
	uchar count;
	wela=1;
	P0=0x7f;//ʹƬѡ����Ϊ�͵�ƽ
	wela=0;
	while(1)
	{
		/*����A/Dת��*/
		adwr=1;
		_nop_();//_nop_()�൱��һ���������ڵ��ӳ٣���Ϊ<intrins.h>�Ŀ⺯��
		adwr=0;
		_nop_();
		adwr=1;
		
		/*���������ʾ"000"���ӳ�ת��ʱ��*/
		for(count=100;count>0;count--)
		{
			display(A1,A2,A3);
		}
		
		/*�����������*/
		P1=0xff;//��ʹ����ܲ���ʾ�κ�����
		adrd=1;
		_nop_();
		adrd=0;
		_nop_();
		ADval=P1;
		adrd=1;
		
		A1=ADval/10;//��λ
		A2=ADval%100/10;//ʮλ
		A3=ADval%100;//��λ
		display(A1,A2,A3);
	}
	return 0;
}	
	
