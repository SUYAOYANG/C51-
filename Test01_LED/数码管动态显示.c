/*
*****************************************************************************************************************************************
*
*		ģ������ �� �����ģ��
*		�ļ����� �� ����ܶ�̬��ʾ.c
*		�汾		 �� v1.0
*		˵��		 �� ʹʵ����ϵ�ǰ6���������ʾ��123456��
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-11	Yang			v1.0�汾���в���
*       v1.1    2020-01-11  Yang      �����������룬��ѡ���ȴ���λ���ݻ������
*
*****************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define WEI_FIRST
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

/*�ȴ��Ͷ�ѡ����*/
#ifndef WEI_FIRST
int main()
{
	while(1)
	{
		/*������һ������ܣ���ʾ����1*/
		dula=1;
		P0=table[1];
		dula=0;
		P0=0xff;//��Ӱ
		wela=1;
		P0=0xfe;
		wela=0;
		delay_ms(1);//��ʱ1���룬�仯���죬�õ�������ʾ���ֲ����Ч��
		
		/*�����ڶ�������ܣ���ʾ����2*/
		dula=1;
		P0=table[2];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xfd;
		wela=0;
		delay_ms(1);
		
		/*��������������ܣ���ʾ����3*/
		dula=1;
		P0=table[3];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xfb;
		wela=0;
		delay_ms(1);
		
		/*�������ĸ�����ܣ���ʾ����4*/
		dula=1;
		P0=table[4];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xf7;
		wela=0;
		delay_ms(1);
		
		/*�������������ܣ���ʾ����5*/
		dula=1;
		P0=table[5];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xef;
		wela=0;
		delay_ms(1);
		
		/*��������������ܣ���ʾ����6*/
		dula=1;
		P0=table[6];
		dula=0;
		P0=0xff;
		wela=1;
		P0=0xdf;
		wela=0;
		delay_ms(1);
	}
	return 0;
}

/*�ȴ���λѡ����*/
#else
int main()
{
	while(1)
	{
		/*������һ������ܣ���ʾ����"1"*/
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[1];
		dula=0;
		delay_ms(1);
		
		/*�����ڶ�������ܣ���ʾ����"2"*/
		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[2];
		dula=0;
		delay_ms(1);
		
		/*��������������ܣ���ʾ����"3"*/
		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=table[3];
		dula=0;
		delay_ms(1);
		
		/*�������ĸ�����ܣ���ʾ����"4"*/
		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[4];
		dula=0;
		delay_ms(1);
		
		/*�������������ܣ���ʾ����"5"*/
		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[5];
		dula=0;
		delay_ms(1);
		
		/*��������������ܣ���ʾ����"6"*/
		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=table[6];
		dula=0;
		delay_ms(1);
		
	}
	return 0;

}
#endif