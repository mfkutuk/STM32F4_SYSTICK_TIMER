/*
	Stm32f4 kartı Cortex M4 işlemcisine sahiptir. Cortex M4 işlemcisi 24 bitlik sistem timerına sahiptir. 
	Bu timer kendine yüklenen değerden sıfıra doğru geriye sayarak çalışır ve sayac sıfıra ulaştığında kesme üretilir. 
	Bu kesme SysTick Timer kesmesidir.
	
	PLL_M=8 PLL_P=2 PLL_Q=4 PLL_N=336   system_stm32f4xx.c(Startup) kütüphansei içinde bulup clock ayarları güncellenmelidir.
	HSE_VALUE=8000000 olarak ayarlanmalıdır.
	SystemCoreClock  168 MHz olarak ayarlanmalıdır.
*/

#include "stm32f4xx.h"

uint16_t count;

void delay_ms(uint32_t delay_ms)
{
count=delay_ms;
while(count){}
}
void SysTick_Handler(void) //kesme oluşturan fonksiyonun adı. 
{
	if(count>0)
	{
		count--;
	}
	
}

int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  GPIO_InitTypeDef led;
  led.GPIO_Mode=0x01;
  led.GPIO_Pin=GPIO_Pin_12;
  GPIO_Init(GPIOD,&led);

  SysTick_Config(SystemCoreClock/1000);  // (1ms) SysTick bir sayma işlemini 168 MHz(168000000) ye göre yapacağından 168.000 sayma işlemi tamamlanması 1 ms sürecektir
	 
  while (1)
  {
	  GPIO_ToggleBits(GPIOD,GPIO_Pin_12);
	  delay_ms(1000);

  }
}



