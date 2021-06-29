#include "stc8.h"
#include "oled.h"
//#include "bmp.h"

int beep=0;
int tt=0;
int tt1=0;
int mode=0;
int times=0;
int light=0;
void beep_init(void)		
{
	TMOD = 0x00;
	TL0 = 0x66;		
	TH0 = 0xFC;		
	TR0 = 1;	
	ET0=1;
	EA = 1;	
}

void spy_init()
{
IT0=1;
EX0=1;
}

void spy_light_init()
{
IT1=1;
EX1=1;
}


 int main(void)
 {	
	  u8 t;
		OLED_Init();			//初始化OLED  
		OLED_Clear()  	; 
		t=' ';
		P37=1;
		P54=1;
		P33=1;
		beep_init();
		spy_init();
		spy_light_init();
//		P36=1;
	while(1) 
	{		
/*		OLED_ShowCHinese(0,0,0);//中
		OLED_ShowCHinese(18,0,1);//景
		OLED_ShowCHinese(36,0,2);//园
		OLED_ShowCHinese(54,0,3);//电
		OLED_ShowCHinese(72,0,4);//子
		OLED_ShowCHinese(90,0,5);//科
		OLED_ShowCHinese(108,0,6);//技
		OLED_ShowString(0,2,"1.3' OLED TEST");
	 	OLED_ShowString(20,4,"2019/11/23");  
		OLED_ShowString(0,6,"ASCII:111");  
		OLED_ShowString(63,6,"CODE:111");  
		OLED_ShowChar(48,6,t);//显示ASCII字符	   
		if(t>'~')t=' ';
		OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 	
		*/
		
    if(P35==1)
		{beep=0;}
		if(P35==0)
		{
		if(mode==1)
			mode=0;
		else if(mode==0)
			 mode=1;
			delay_ms(500);
	   beep=1;}
		
		if(light==0)
			P37=0;
		
		if(P32==0)
		{
	OLED_ShowString(0,2,"None human");
	P37=0;
	}
	if(P32==1)
		{
	if(light==1)
	P37=1;
	OLED_ShowString(0,2,"Human");
	
	}
	
	
		OLED_ShowNum(50,0,times/10,1,2);
		OLED_ShowNum(60,0,times%10,1,2);
		
		
		if (mode==1)
		{
	  OLED_ShowString(0,4,"Logged");
		light=0;
		}
		if (mode==0)
		{
		times=0;
		OLED_ShowString(0,4,"Not Logged");
		P55=1;
		}
		
		if (light==1)
		{
	  OLED_ShowString(50,6,"ON");
		}
		if (light==0)
		{
		OLED_ShowString(50,6,"OFF");
		}
		
		
		OLED_ShowString(0,6,"Light");
		OLED_ShowString(0,0,"Times");	
		delay_ms(50);
		OLED_Clear();
//		delay_ms(500);
//		OLED_DrawBMP(0,0,128,8,BMP1);  //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
//		delay_ms(50);
//		OLED_DrawBMP(0,0,128,8,BMP2);
//		delay_ms(50);
 }	  
}


void beep_bi()  interrupt 1
{
tt++;
if(tt==1000)
{
if(mode==1)
{	
	P55=~P55;
}
tt=0;
}
}

void spy_bi()  interrupt  0
{
if(mode==1)
{
times++;
}
}


void spy_light_bi()  interrupt  2
{
	if(light==1)
		light=0;
	else if(light==0)
	  light=1;
}

