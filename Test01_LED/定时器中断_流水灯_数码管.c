/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ�顢�����ģ��
*		�ļ����� �� ��ʱ���ж�_�����_�����.c
*		�汾		 �� v1.0
*		˵��		 �� ��ʱ��0�ķ�ʽ1ʵ�ֵ�һ���������200ms�����˸����ʱ��1�ķ�ʽ1ʵ�������ǰ��λ59sѭ����ʱ
*		�޸ļ�¼ ��
*			  �汾��	����				����			˵��
*				v1.0		2020-01-11	Yang			v1.0�汾���в���
*				v1.1		2020-01-11  Yang			�ĳɿ�����ʾ���ʱ��24Сʱ��ʱ��,����Ƹ�Ϊ���1s��˸
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit dula=P2^6;
sbit wela=P2^7;
sbit led=P1^0;
uint ge,shi,bai,qian,wan,shiWan;
uint NumT0,NumT1_1,NumT1_2,NumT1_3,NumT1_4;

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
void display(uint ge,uint shi,bai,qian,wan,shiWan)
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
	
	/*��ʾ��λ*/
	wela=1;
	P0=0xf7;
	wela=0;
	dula=1;
	P0=table[bai];
	dula=0;
	delay_ms(5);
	
	/*��ʾǧλ*/
	wela=1;
	P0=0xfb;
	wela=0;
	dula=1;
	P0=table[qian];
	dula=0;
	delay_ms(5);
	
	/*��ʾ��λ*/
	wela=1;
	P0=0xfd;
	wela=0;
	dula=1;
	P0=table[wan];
	dula=0;
	delay_ms(5);
	
	/*��ʾʮ��λ*/
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=table[shiWan];
	dula=0;
	delay_ms(5);
	
}


int main()
{
	TMOD=0x11;
	/*���ö�ʱ��0Ϊ������ʽ1��50ms*/
	TH0=(65536-45872)/256;
	TL0=(65536-45872)%256;
	EA=1;
	ET0=1;
	TR0=1;
	
	/*���ö�ʱ��1Ϊ������ʽ1,50ms*/
	TH1=(65536-45872)/256;
	TL1=(65536-45872)%256;
	EA=1;
	ET1=1;
	TR1=1;
	
	while(1)
	{
		display(ge,shi,bai,qian,wan,shiWan);
	}
	
}	

/*��ʱ��0�жϣ�ʵ�ַ���Ƽ��1s��˸*/
void T0_Time() interrupt 1
{
	/*��װ��ֵ,50ms*/
	TH0=(65536-48572)/256;
	TH1=(65536-48572)%256;
	
	NumT0++;
	if(NumT0==20)//��1s
	{
		NumT0=0;
		led=~led;
	}
	
}

/*��ʱ��1�жϣ�ʵ�������ǰ��λ24Сʱ��ʱ��ѭ��*/
void T1_Time() interrupt 3
{
	/*��װ��ֵ��50ms*/
	TH1=(65536-48572)/256;
	TL1=(65536-48572)%256;
	
	NumT1_1++;
	if(NumT1_1==20)//��1��
	{
		NumT1_1=0;
		NumT1_2++;//��¼����
		if(NumT1_2==60)
	  {
			NumT1_2=0;
			NumT1_3++;//��¼����
			if(NumT1_3==60)
			{
				NumT1_3=0;
				NumT1_4++;//��¼Сʱ
				if(NumT1_4==24)
				{
					NumT1_4=0;
				}
			}
		}
		ge=NumT1_2%10;
		shi=NumT1_2/10;
		bai=NumT1_3%10;
		qian=NumT1_3/10;
		wan=NumT1_4/10;
		shiWan=NumT1_4%10;
	}
	
}