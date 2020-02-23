#ifndef __24C02_H
#define __24C02_H

#define uchar unsigned char
#define uint unsigned int

bit  write=0;
sbit SDA=P2^0;
sbit SCL=P2^1;

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

#endif
