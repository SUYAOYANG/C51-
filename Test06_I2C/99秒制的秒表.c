/*
***********************************************************************************************************************************************
*
*		ģ������ �� E2PROMģ��AT24C02
*		�ļ����� �� 90���Ƶ����.c
*		�汾		 �� v1.0
*		˵��		 �� ���ö�ʱ������һ��0~99��仯�������ʾ��������ϣ������仯д��AT24C02��
*								���ر�ʵ����Դ�����ٴδ򿪵�Դʱ����Ƭ���ȴ�AT24C02��ȡԭ��д������֣����Ŵ��������仯����ʾ���������
*		�޸ļ�¼ ��
*			  �汾��		 ����				����			˵��
*				v1.0		2020-01-17	Yang			v1.0�汾���в���
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

bit  write=0;
sbit SDA=P2^0;
sbit SCL=P2^1;
sbit dula=P2^6;
sbit wela=P2^7;

uchar second,count;//second����
/*��������ֱ�*/
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71
};

/*Ӳ����ʱ��������ʱ4~5΢��*/
void delay_us_hard()
{;;}

/*�����ʱ��������ʱn����*/
void delay_ms_soft(uint n)
{
	uint i,j;
	for(i=n;i>0;i--)
		for(j=110;j>0;j--);
}

/*��ʼ�ź�,SDA�½��ش���*/
void I2C_start()
{
	SDA=1;
	delay_us_hard();
	SCL=1;
	delay_us_hard();
	SDA=0;
	delay_us_hard();
}

/*ֹͣ�źţ�SDA�����ش���*/
void I2C_stop()
{
	SDA=0;
	delay_us_hard();
	SCL=1;
	delay_us_hard();
	SDA=1;
	delay_us_hard();
}

/*Ӧ���źţ�SDA���������أ��ٴ����½���*/
void I2C_respond()
{
	uchar i;
	SCL=1;
	delay_us_hard();
	while(SDA==1&&i<250)i++;//�ȴ��͵�ƽ��������һֱ�ȴ�,�ȴ�һ����������Ӧ�����˳�
	SCL=0;
	delay_us_hard();
}

/*��ʼ��,SDA=1,SCL=1*/
void I2C_init()
{
	SDA=1;
	delay_us_hard();
	SCL=1;
	delay_us_hard();
}

/*дһ���ֽ�*/
void I2C_write_byte(uchar data_val)
{
	uchar i,temp;
	temp=data_val;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;//��������һλ�����λ����CY�Ĵ���
		SCL=0;
		delay_us_hard();
		SDA=CY;//��CY�Ĵ��������ݴ�����������
		delay_us_hard();
		SCL=1;//SCL���ߣ�����д����
		delay_us_hard();
	}
	/*�ع�ԭʼ״̬*/
	SCL=0;
	delay_us_hard();
	SDA=1;
	delay_us_hard();
}

/*��һ���ֽ�*/
uchar I2C_read_byte()
{
	uchar i,j;
	SCL=0;//�Ȱ�ʱ������
	delay_us_hard();
	SDA=1;//����������
	delay_us_hard();
	for(i=0;i<8;i++)
	{
		SCL=1;//�ٰ�ʱ�����ߣ���������λ��
		delay_us_hard();
		j=(j<<1)|SDA;//j����һλ��SDA���л����㣬���ν�8��������λ����j����ɽ���
		SCL=0;//����ʱ�����ͣ�ֹͣ����λ��
		delay_us_hard();
	}
	return j;
}

/*ָ����ַд����*/
void I2C_write_data(uchar address,uchar data_val)
{
	I2C_start();
	I2C_write_byte(0xa0);//д��Ƭѡ�źŵĿ�����,����д����
	I2C_respond();
	I2C_write_byte(address);//доƬ�ڵĴ�������Ԫ�ӵ�ַ
	I2C_respond();
	I2C_write_byte(data_val);
	I2C_respond();
	I2C_stop();
}

/*ָ����ַ������*/
uchar I2C_read_data(uchar address)
{
	uchar temp;
	I2C_start();
	I2C_write_byte(0xa0);//д��Ƭѡ�źŵĿ����֣�����д����
	I2C_respond();
	I2C_write_byte(address);//доƬ�ڵĴ洢����Ԫ�ӵ�ַ
	I2C_respond();
	I2C_start();
	I2C_write_byte(0xa1);//д��Ƭѡ�źŵĿ����֣����ж�����
	I2C_respond();
	temp=I2C_read_byte();
	I2C_stop();
	
	return temp;
}

/*��ʾ����ܺ���λ*/
void display(uchar ge,uchar shi)
{
	/*��ʾ��λ*/
	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[ge];
	dula=0;
	delay_ms_soft(5);
	
	/*��ʾʮλ*/
	wela=1;
	P0=0xdf;
	wela=0;
	dula=1;
	P0=table[shi];
	dula=0;
	delay_ms_soft(5);
}

/*������*/
void main()
{
	/*��ʼ��I2C����ȡE2PPROM������*/
	I2C_init();
	second=I2C_read_data(2);
	if(second>100)//������룬��second����
	{
		second=0;
	}
	
	/*����ʱ��0���м�ʱ�ж�*/
	TMOD=0x01;//ʱ��0��������ʽ1
	TH0=(65536-50000)/256;//0.05msһ��
	TL0=(65536-50000)%256;
	TR0=1;
	EA=1;
	ET0=1;
	
	/*����������ʾ�����,��1sʱ�������д��E2PPROM*/
	while(1)
	{
		display(second/10,second%10);
	
		if(write==1)//��1s
		{
			write=0;
			I2C_write_data(2,second);
		}
	}
}

/*��ʱ��0�жϷ�����*/
void T0_time() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	count++;
	if(count==20)//��1s
	{
		count=0;
		write=1;//1sд��E2PPROM
		second++;//������1
		if(second==100)//��ʱ100s���ٴ��㿪ʼ��ʱ
		{
			second=0;
		}
	}
}