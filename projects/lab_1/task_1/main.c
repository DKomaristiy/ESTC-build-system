#include <stm32f4xx.h>





void delay(uint32_t value);
void SetSysClockTo84(void);

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


   RCC_DeInit();
   RCC_HSICmd(ENABLE);

   RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

   while (RCC_GetSYSCLKSource() != 0x00);


   GPIO_InitTypeDef GPIO_InitStructure;


   /* Enable peripheral clock for LEDs and buttons port */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

   /* Init LEDs */
   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
   GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
   GPIO_Init(GPIOE, &GPIO_InitStructure);

   /* Turn all the leds off */
   GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);





   RCC_ClocksTypeDef RCC_Clocks;
   RCC_GetClocksFreq(&RCC_Clocks);

   /* if (RCC_Clocks.SYSCLK_Frequency == 84000000 ) // проверка выставилась частота или нет
  {
    GPIO_ResetBits(GPIOA, GPIO_Pin_8);
  }
  else
  {
    GPIO_ResetBits(GPIOA, GPIO_Pin_9);
  }

delay(5000000);

*/

   while (1)
   {

      int state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
      int state_1 = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1);
      if (!state)
      {

         RCC_DeInit();
         RCC_HSICmd(ENABLE);

         RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

         while (RCC_GetSYSCLKSource() != 0x00);


      }

      else if (!state_1)
      {

         SetSysClockTo84();
      }


      GPIO_ResetBits(GPIOA,GPIO_Pin_10 );
      delay(2000000);
      GPIO_SetBits(GPIOA, GPIO_Pin_10 );
      delay(2000000);

   }
   /*
while (1)
  {
     for (int j=0; j<3;j++) // 1 to 3 leds
     {
        GPIO_ResetBits(GPIOA,GPIO_Pin_8 << j );
        delay(SWITCH_DELAY);
        GPIO_SetBits(GPIOA, GPIO_Pin_8 << j);
     }

  }

*/
}


void SetSysClockTo84(void)
{
  int HSEStartUpStatus;	
  RCC_DeInit();
  /* Enable HSE */
  RCC_HSEConfig( RCC_HSE_ON);
  
  
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
       
     RCC_PLLConfig(RCC_PLLSource_HSE,8,336,4,4);
          
     RCC_PLLCmd( ENABLE);

        /* Wait till PLL is ready */
     while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
     {
     }

     /* Select PLL as system clock source */
     RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);

     /* Wait till PLL is used as system clock source */
     while (RCC_GetSYSCLKSource() != 0x08)
     {
     }

  }
}

