#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//Var 4
//Out A3 
//t= 15
//T= 30

void Delay(uint32_t nTime);

int main(void)
{
  int i;

  /* Initialize LED which connected to PC13, Enable the Clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);
	
  GPIO_InitTypeDef  GPIO_InitStructure;
	//SET pin 3A and 11B to output mode
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_11; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		

	if (SysTick_Config(SystemCoreClock / 1000))
     while (1);
	
  while (1)
  { 
		//LED ON
		GPIOB->ODR=GPIO_Pin_11;
		GPIOA->ODR=GPIO_Pin_3;
		Delay(5);
		//11B OFF
		GPIOB->ODR=~GPIO_Pin_11;
		Delay(10);
		//3A OFF
		GPIOA->ODR=~GPIO_Pin_3;
		Delay(30);
  }
}

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void){
    if (TimingDelay != 0x00)
        TimingDelay --;
}
