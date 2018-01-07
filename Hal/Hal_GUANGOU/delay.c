/**
********************************************************
*
* @file      delay.c
* @author    Gizwtis
* @version   V2.3
* @date      2015-07-06
*
* @brief     机智云.只为智能硬件而生
*            Gizwits Smart Cloud  for Smart Products
*            链接|增值ֵ|开放|中立|安全|自有|自由|生态
*            www.gizwits.com
*
*********************************************************/

#include "delay.h"

static uint8_t  fac_us=0;																		//us延时倍乘数
static uint16_t fac_ms=0;//ms延时倍乘数
		    								   
void Delay_us(uint32_t nus)
{		
		uint32_t temp;  
		SysTick->LOAD = nus*fac_us;  //延时10us,10*9 = 90,装到load寄存器中
		SysTick->VAL=0x00;//计数器清0
		SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
		do  
		{  
			 temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
		}  
		while(temp & 0x01 && !(temp &(1<<16)));//查询
		SysTick->CTRL = 0x00;//关闭定时器
		SysTick->VAL = 0x00;//清空val,清空定时器
}


void Delay_ms(uint16_t nms)
{	 		  	  
		uint32_t temp;  
		SysTick->LOAD = nms*fac_ms;//延时10ms,10*9 = 90,装到load寄存器中
		SysTick->VAL=0x00;//计数器清0
		SysTick->CTRL = 0x01;//配置异常生效,也就是计数器倒数到0时发出异常通知
		do  
		{  
			 temp = SysTick->CTRL;//时间到,该位将被硬件置1,但被查询后自动清0
		}  
		while(temp & 0x01 && !(temp &(1<<16)));//查询
	
		SysTick->CTRL = 0x00;//关闭定时器
		SysTick->VAL = 0x00;//清空val,清空定时器
} 
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
/*------------------------------------------------
 mSÑÓÊ±º¯Êý£¬º¬ÓÐÊäÈë²ÎÊý unsigned char t£¬ÎÞ·µ»ØÖµ
 unsigned char ÊÇ¶¨ÒåÎÞ·ûºÅ×Ö·û±äÁ¿£¬ÆäÖµµÄ·¶Î§ÊÇ
 0~255 ÕâÀïÊ¹ÓÃ¾§Õñ12M£¬¾«È·ÑÓÊ±ÇëÊ¹ÓÃ»ã±à
------------------------------------------------*/
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //´óÖÂÑÓÊ±1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
