/**
	*˵����Ϊ�˽�һ���˽�ָ��ʹ�÷������鿴�������ʹ洢����ֵ
	*���ߣ�Yang
	*ʱ�䣺2020/1/30
	*/
	
#include <reg52.h>

#define uchar unsigned char
#define uint unsigned int

/*����16���������*/
uchar code temp[]=
{
	0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27
};

void main()
{
	uchar i;
	uint j;
	uchar code *finger;//�������code����ָ��
	do
	{
		finger=&temp[0];//ȡ�������׵�ַ
		for(i=0;i<16;i++)
		{
			for(j=0;j<3000;j++);//�ӳ�һ��ʱ��
			P1=*finger;
			finger++;
		}
	}while(1);
}
