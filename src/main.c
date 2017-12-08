#include "CMSIS/stm32f10x.h"

void button(void);

void twinkling(void);

void garland(void);

int main(void)
{
	//button();
	//twinkling();
	garland();
	return 0;
}

void button(void)
{
	RCC-> APB2ENR|=1<<2;//power on the A port	
	GPIOA->CRL&=~(0xF);//setting last 4 bits to zero
	GPIOA->CRL|=0x4;//input floating PA.0
	
	RCC-> APB2ENR|=(1<<4);//power on the C port
	GPIOC->CRH&=~(0xF);//setting last 4 bits to zero
	GPIOC->CRH|=0x3;//output push pull at 50 MHz. PC.8
	
	while(1)
	{
		if (GPIOA->IDR & 1)//0th pin. Button is pressed
		{
			GPIOC->ODR|=1<<8;//8th pin HIGH
		}
		else//not pressed
		{
			GPIOC->ODR&=~(1<<8);//8th pin LOW
		}
	}
}
void twinkling(void)
{
	RCC->APB2ENR|=1<<4;//power on port C
	GPIOC->CRH&=~(0xFF);//setting last 8 bits to zero
	GPIOC->CRH|=0x11;//8th and 9th pins sets to output push pull at 10MHz
	
	uint32_t i=0;
	while(1)
	{
		GPIOC->ODR&=~(1<<9);//9th low
		GPIOC->ODR|=0x1<<8;//8th high
		for(i=0;i<10000000;i++){}
		
		GPIOC->ODR&=~(1<<8);//8th low			
		GPIOC->ODR|=0x1<<9;	//9th high
		for(i=0;i<10000000;i++){}	
	}
}
void garland()
{
	RCC->APB2ENR|=3<<2;//power on A and B ports
	
	GPIOB->CRL&=~(0xFFF);//setting last 12 bits to zero
	GPIOB->CRL|=0x444;//input floating PB.0,1,2
	
	GPIOA->CRL&=0xF;//only first 4 bits do not sets to zero
	GPIOA->CRL|=0x33333330;//output push pull at 50 MHz at PA.1-7
	while(1)
	{
		GPIOA->ODR&=0x1;//turn off all the LEDs
		GPIOA->ODR|=(2<<(GPIOB->IDR&7));//turn on the desired LED not touching PA.0
	}
}
