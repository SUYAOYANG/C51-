/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ��
*		�ļ����� �� ������������ķ�������.c
*		�汾		 �� v1.0
*		˵��		 �� ��v1.0�����ü�����0�ķ�ʽ1����һ����������GND���ţ���һ��ȥ�Ӵ�T0(P3^4)���ţ�ÿ�Ӵ�һ�£���������һ����
*								�����Ƶ���ֵ��ʾ������ܵ�ǰ��λ������100ʱ���㣬�ٴ�ͷ����
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-22	Yang			v1.0�汾���в���,�����ߴ�GND�ӵ�P1^0�˿�
*				v1.1		2020-01-22  Yang			��ʱ��0���м�ʱ��������1���м����������ж϶�ȡ������1�����ݣ������߶˽ӵ�T1(P3^5)����
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define T0_COUNT
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;
sbit wela=P2^7;
sbit port_out=P1^0;

uchar count,NumTotal;
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

/***************v1.0�汾��T0��������*******************/
#ifdef T0_COUNT

/*��ȡT0(P3^4)���ŵ�����*/
uchar T0_read()
{
	uchar high_1,high_2,low;
	uchar value;
	
	while(1)
	{
		/*�˿�P1^0��2Hz��Ƶ������ߵ͵�ƽ*/
		port_out=1;
		delay_ms(500);
		port_out=0;
		
		/*��ֹ��������λʱ�����п��ܶ������ݣ����TH0�ļĴ�����Ҫ��ȡ����,ȷ����ȡ��ʱ��û�з�����λ*/
		high_1=TH0;
		low=TL0;
		high_2=TH0;
		if(high_1==high_2)//ǰ�����ζ�ȡ��ͬȷ����ȡ��ȷ���˳�
			break;
	}
	
	value=256*high_1+low;
	return value;
}

/*������*/
void main()
{
	uchar num1,num2;
	uchar result;
	/*����������0*/
	TMOD=0x05;//���ü�����0������ʽ1��00000101��
	TH0=0;
	TL0=0;
	TR0=1;
	while(1)
	{
		result=T0_read();
	 	
		/*����100����*/
		if(result>=100)
		{
			result=0;
			TH0=0;
			TL0=0;
		}
		num1=result%10;//��λ
		num2=result/10;//ʮλ
		display(num1,num2);
	}

}

/***************v1.1�汾��T0����ʱ����T1��������*******************/
#ifdef T1_COUNT

void main()
{
	/*��ʱ��0��Ϊ������ʽ2��������1��Ϊ������ʽ1*/
	TMOD=0x51;//������ʽ01010010
	TH0=(65536-47852)%256;//װ��ֵ
	TL0=(65536-47852)/256;
	TR0=1;
	EA=1;
	ET0=1;
	
	TH1=0;
	TL1=0;
	TR1=1;
	
	while(1)
	{
		if(count>=100)
		{
			count=0;
		}
	}
}

/*��ʱ��0�жϷ�����*/
void T1_time() interrupt 1
{
	count++;
	uchar high_1,high_2,low;
	uchar value;
	
	while(1)
	{
		/*��ֹ��������λʱ�����п��ܶ������ݣ����TH1�ļĴ�����Ҫ��ȡ����,ȷ����ȡ��ʱ��û�з�����λ*/
		high_1=TH1;
		low=TL1;
		high_2=TH1;
		if(high_1==high_2)//ǰ�����ζ�ȡ��ͬȷ����ȡ��ȷ���˳�
		{
			break;
		}
	}
	value=high_1*256+low;
	display(value%100,value/100);
}
#endif