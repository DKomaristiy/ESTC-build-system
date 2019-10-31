#include <stm32f4xx.h>


void delay(uint32_t value);

#define SWITCH_DELAY    ((uint32_t)2000000)
void delay(uint32_t value)
{
  for (uint32_t i=0; i<value;i++)
  {
    __NOP();	  
  }	  

}



int main(void)
{ 

  RCC_HSICmd(ENABLE);
  RCC_PLLConfig(RCC_PLLSource_HSI,10,250,4,4);  /* 100MHz set  */	
  RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
  RCC_PLLCmd(ENABLE);  



  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);

  /* Enable peripheral clock for LEDs and buttons port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  /* Init LEDs */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


  /* раскоментировать для проверки 2 пункта
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);

  if (RCC_Clocks.SYSCLK_Frequency == 84000000 )
  {
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
  }
  else
  {
    GPIO_SetBits(GPIOD, GPIO_Pin_15);	  
  }
  */


	
  /* Turn all the leds off */
  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

/* 1 to 4 leds 
  while(1)
  {
    for (int j=0; j<4;j++)
    {	    
      GPIO_ResetBits(GPIOD,GPIO_Pin_12 << j );
      delay(SWITCH_DELAY);
      GPIO_SetBits(GPIOD, GPIO_Pin_12 << j);
    }
  
  }
*/

  /*  all leds in an endless loop
  while(1)
  {
      GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 );
      delay(SWITCH_DELAY);
      GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 );
  } 
  
  */


  

  uint32_t flag = 0;

  while (1)
  {
    int state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
    if (!state)
    {
      if (flag == 1)
        {
          RCC_DeInit();
          RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
          RCC_HSICmd(ENABLE);
         }
       else if (flag == 0 )
       {	 
         RCC_DeInit();  
	 RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);
         RCC_HSEConfig(RCC_HSE_ON);
       }  


      GPIO_ResetBits(GPIOD,GPIO_Pin_12 );
      delay(SWITCH_DELAY);
      GPIO_SetBits(GPIOD, GPIO_Pin_12 );

    }

  }

}
