#include<lpc214x.h>
#include "delay.h"
__irq void Ext_int(void);
char s=0;
int main()
{
	PINSEL0=1<<15|1<<14;
	IO1DIR=1<<16;
	EXTMODE=1<<2;// edge sensitive
	EXTPOLAR=1<<2;//Rising edge
	VICIntSelect&=~(1<<16);// selecing as IRQ category
	VICVectCntl0=16|1<<5;// selecting priority as slot0 for EINT0
	VICVectAddr0=(unsigned int)Ext_int;
	EXTINT=1<<2;
	VICIntEnable=1<<16;//EXT0 enable as VIC
	int i;
	char seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	IO0DIR=0x7F;
	while(1)
	{
		for(i=0;i<=9;i++)
		{
	IO0SET=seg[i];
	delay(100);
	IO0CLR=seg[i];
	}
}
}
__irq void Ext_int(void)
{
	EXTINT=1<<2;
	VICVectAddr=0;
	if(s==0)
	{
		IOSET1=1<<16;
		s=1;
	}
	else
		{
			IOCLR1=1<<16;
			s=0;
	}
}