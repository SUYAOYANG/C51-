/*
***********************************************************************************************************************************************
*
*		模块名称 ： 发光灯模块
*		文件名称 ： 方式2应用.c
*		版本		 ： v1.0
*		说明		 ： 定时器0的工作方式2实现第二个发光灯以1s间隔闪烁，方式2为8位初值自动重装的定时器/计数器
*		修改记录 ：
*			  版本号	日期				作者			说明
*				v1.0		2020-01-19	Yang			v1.0版本进行测试
*			
*
***********************************************************************************************************************************************
*/

#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit led=P1^1;
uint count;

void main()
{
	TMOD=0x02;//定时器0，工作方式2
	TH0=6;//装初值
	TL0=6;
	EA=1;
	ET0=1;
	TR0=1;
	while(1)
	{
		if(count>=3686)
		{
			count=0;
			led=~led;
		}
	}

}

/*定时器0中断服务函数*/
void T0_time() interrupt 1
{
	count++;
}