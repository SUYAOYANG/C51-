/*
***********************************************************************************************************************************************
*
*		ģ������ �� �����ģ��
*		�ļ����� �� ��Ƭ��ͨ��_����.c
*		�汾		 �� v1.0
*		˵��		 �� ������һ����Ƭ�����͹����ļ�ֵ������Ӧ��ֵ��0~F��ʽ��ʾ���������
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-23	Yang			v1.0�汾���в���
*				v1.1		2020-01-23	Yang			���ӷ������ݵĹ���
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

//#define ONLY_RX
#define TX_RX

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

/*�������ݺ���*/
void SendData(uchar key_num)
{
	SBUF=key_num;
	while(!TI);//�ȴ��������
	TI=0;//������ɺ�TI�������㣬Ԥ����һ�ַ���
}

/*��ʾ�����ǰһλ*/
void display(uchar num)
{
	/*��ʾ������*/
	P0=table[num];
	dula=1;
	dula=0;
	
}

/*������̼��*/
void MatrixKeyScan()
{
	uchar key,temp;
	/*temp=P3Ϊɨ��P3�˿�*/
	
	/*����һ��*/
	P3=0xfe;//��һ��Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xee:
					key=0;
					break;
				
				case 0xde:
					key=1;
					break;
				
				case 0xbe:
					key=2;
					break;
				
				case 0x7e:
					key=3;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			SendData(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*���ڶ���*/
	P3=0xfd;//�ڶ���Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xed:
					key=4;
					break;
				
				case 0xdd:
					key=5;
					break;
				
				case 0xbd:
					key=6;
					break;
				
				case 0x7d:
					key=7;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			SendData(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*��������*/
	P3=0xfb;//������Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xeb:
					key=8;
					break;
				
				case 0xdb:
					key=9;
					break;
				
				case 0xbb:
					key=10;
					break;
				
				case 0x7b:
					key=11;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			SendData(key);//�Ȱ����ɿ�������ʾ����
		}
	}
	
	/*��������*/
	P3=0xf7;//������Ϊ�͵�ƽ
	temp=P3;
	temp=temp&0xf0;//ת��Ϊ�е�ƽ
	if(temp!=0xf0)//��һ�μ�ⰴ���Ƿ���
	{
		delay_ms(10);//��ʱ����
		temp=P3;
		temp=temp&0xf0;
		if(temp!=0xf0)//�ڶ��μ��
		{
			temp=P3;
			switch(temp)
			{
				case 0xe7:
					key=12;
					break;
				
				case 0xd7:
					key=13;
					break;
				
				case 0xb7:
					key=14;
					break;
				
				case 0x77:
					key=15;
					break;
			}
			while(temp!=0xf0)//��ⰴ���Ƿ��ɿ���û�ɿ���һֱ���
			{
				temp=P3;
				temp=temp&0xf0;
			}
			SendData(key);//�Ȱ����ɿ�������ʾ����
		}
	}
}

/*****************����������**********************/
#ifdef ONLY_RX

/*������*/
void main()
{
	/*������ʱ��1����Ϊ������ʽ2���뷢�ͷ�һ��*/
	TMOD=0x20;
	TL1=0xfe;
	TH1=0xfe;
	TR1=1;
	
	/*�贮�ڹ�����ʽΪ������ʽ1*/
	REN=1;
	SM0=1;
	SM1=0;
	
	/*�����ж�*/
	EA=1;
	ES=1;
	
	/*��������ܵ�λѡ*/
	P0=0xc0;//ѡ����������ܣ�6λ
	wela=1;
	wela=0;
	
	while(1);//�˴����ϲ�ѯ�ж�
}

/*�����жϷ�����*/
void Serial() interrupt 5
{
	uchar temp;
	RI=0;
	temp=SBUF;
	display(temp);
}

/*****************�������������**********************/
#ifdef TX_RX

/*������*/
void main()
{
	/*������ʱ��1����Ϊ������ʽ2�����Զ���װ��ֵ*/
	TMOD=0x20;
	TL1=0xfe;
	TH1=0xfe;
	TR1=1;
	
	/*������Ϊ������ʽ1*/
	SM0=0;
	SM1=1;
	EA=1;
	ES=1;
	REN=1;
	
	while(1)
	{
		ES=0;
		delay_ms(5);
		MatrixKeyScan();
		ES=1;
	}

}

/*�����жϷ�����*/
void Serial() interrupt 5
{
	uchar temp;
	RI=0;
	temp=SBUF;
	display(temp);
}

#endif