/*
***********************************************************************************************************************************************
*
*		模块名称 ： 串口模块
*		文件名称 ： 串口接收发送.c
*		版本		 ： v1.0
*		说明		 ： 上位机通过串口助手发送字符"X"给单片机，单片机返回给上位机"I get X"
*		修改记录 ：
*			  版本号	日期				作者			说明
*				v1.0	2020-01-13	Yang			v1.0版本进行测试
*				
*
***********************************************************************************************************************************************
*/

#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int
uchar temp,FlagRx;
uint i;
uchar code table[]="I get ";

/*进行定时器、串口、中断初始化*/
void Init()
{
	/*定时器1*/
	TMOD=0x20;//工作方式2
	TH1=0xfd;
	TL1=0xfd;//装初值
	TR1=1;//此处不用开启定时器1中断（ET1=0）,因为工作方式2是8位初值自动重装的8位定时器/计数器
	
	/*串口*/
	SM0=0;
	SM1=1;//工作方式1
	REN=1;
	
	
	/*中断*/
	EA=1;//开启总中断
	ES=1;//开启串口中断
}	

int main()
{
	Init();
	while(1)
	{
		if(FlagRx==1)//接收完成,开始发送
		{
			ES=0;
			for(i=0;i<6;i++)
			{
				SBUF=table[i];
				while(!TI);//等待发送完成
				TI=0;
			}
			SBUF=temp;
			while(!TI);
			TI=0;
			ES=1;
			FlagRx=0;
		}
	
	}
	return 0;

}

/*串口中断服务程序,接收字符*/
void Ser_Rx_Msg() interrupt 4
{
	RI=0;
	temp=SBUF;
	FlagRx=1;
}