/*
***********************************************************************************************************************************************
6
*		ģ������ �� ����ģ��
*		�ļ����� �� ��������.c
*		�汾		 �� v1.0
*		˵��		 �� ��Ƭ�����ͨ�ţ�Լ��һ�δ��͵�����Ϊ16B,�ӻ���ַΪ02H
*		�޸ļ�¼ ��
*			  �汾��		����				����			˵��
*				v1.0		2020-01-27	Yang			v1.0�汾���в���
*				
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

#define SLAVE 0x02
#define LENGTH 16
uchar rbuf[16];
uchar code tbuf[16]={"master transmit"};

/*���͸�λ�ź�*/
void error()
{
	SBUF=0xff;
	while(TI!=1);
	TI=0;
}

/**����:master()
	*���ܣ�������ӻ�����ͨ�ţ���������������ӻ�����������Ĺ����ж�Ϊ�������ݻ��������
	*���룺�ӻ���ַaddress,����command
	*�����0
	*/
uchar master(uchar address,uchar command)
{
	uchar i,temp,pbuf;
	while(1)
	{
		SBUF=SLAVE;//�����е�ַ
		while(TI!=1);//�ȴ�����������
		TI=0;
		while(RI!=1);//�ȴ��ӻ�Ӧ��
		RI=0;
		if(SBUF!=address)//����ַ�����͸�λ�ź�
		{
			error();
		}
		
		else
		{
			TB8=0;//����ַ��־����
			SBUF=command;//��������
			while(TI!=1);
			TI=0;
			while(RI!=1);
			RI=0;
			temp=SBUF;
			
			/*�ӻ�û�յ������RB8=0����λ�����ź�*/
			if(temp&&0x08==0x08)
			{
				TB8=1;
				error();
			}
			
			/*�ӻ��յ����������ʼִ��*/
			else
			{
				/*��������*/
				if(command==0x01)
				{
					if(temp&&0x01==0x01)//RRDY=1,�ӻ����վ���
					{
						do
						{
							pbuf=0;//��У���
							
							/*��ʼ����16B����*/
							for(i=0;i<LENGTH;i++)
							{
								SBUF=tbuf[i];//����һ����
								pbuf+=tbuf[i];
								while(TI!=1);
								TI=0;
							}
							
							/*����У���*/
							SBUF=pbuf;
							while(TI!=1);
							TI=0;
							while(RI!=1);
							RI=0;
							
							return 0;
						}while(SBUF!=0);
						
						TB8=1;//����������ϣ��õ�ַ��־
					}
					return 0;
					
				}
				
				/*��������*/
				else if(command==0x02)
				{
					if(temp&&0x02==0x02)//TRDY=1,�ӻ����;���
					{
						while(1)
						{
							pbuf=0;//��У���
							
							for(i=0;i<LENGTH;i++)
							{
								while(RI!=1);
								RI=0;
								rbuf[i]=SBUF;//����һ����
								pbuf+=rbuf[i];//������У������ݴ��
							}
							
							/*���ռ����*/
							while(RI!=1);
							RI=0;
							if(SBUF==pbuf)
							{
								SBUF=0x00;//У�����ͬ��00
								while(TI!=1);
								TI=0;
								break;
							}
							
							else
							{
								SBUF=0xff;//У��Ͳ�ͬ��ff
								while(TI!=1);
								TI=0;
							}
						}
						
						TB8=1;//�õ�ַ��־
						return 0;
					}
				}
			
			}
			
		}
	}

}

/*������*/
void main()
{
	/*������ʱ��1��������ʽ2*/
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	
	PCON=0x00;//���ʿ��ƼĴ���
	SCON=0xf8;//���п�Ϊ��ʽ3
	
	master(SLAVE,0x01);
	master(SLAVE,0x02);
	
	while(1);
}