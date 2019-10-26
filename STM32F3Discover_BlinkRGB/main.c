#include "stm32f30x.h"
#include "stm32f3_discovery.h"
#include "stm32f30x_it.h"

#define BSRR_VAL 0xE000 // 14 0 0 0 0 = 11100 0000 0000 0000
GPIO_InitTypeDef        GPIO_InitStructure;

int main(void)
{
  /* GPIOE Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  
  /* Configure PE14 and PE15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 |  GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  while (1)
  {
    GPIOE->BSRR = GPIO_Pin_15;
    GPIOE->BRR = GPIO_Pin_14;
    GPIOE->BRR = GPIO_Pin_13;
    delay(800000);

    GPIOE->BRR = GPIO_Pin_15;
    GPIOE->BSRR = GPIO_Pin_14;
    GPIOE->BRR = GPIO_Pin_13;
    delay(800000);

    GPIOE->BRR = GPIO_Pin_15;
    GPIOE->BRR = GPIO_Pin_14;
    GPIOE->BSRR = GPIO_Pin_13;
    delay(800000);
  }
}

void delay(int cycles)
{
	volatile int i = 0, j = 0;
	for (i = cycles; i > 0; i --)
	{
		j++;
	}
}
