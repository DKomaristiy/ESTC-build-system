#include <stm32f4xx.h>


#define RED   GPIO_Pin_8
#define BLUE  GPIO_Pin_9
#define GREEN GPIO_Pin_10


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


static int configure_leds(void)
{
   GPIO_InitTypeDef leds_init_structure;
   /* Enable clocking for LEDS */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   leds_init_structure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
   leds_init_structure.GPIO_Mode = GPIO_Mode_OUT;
   leds_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
   leds_init_structure.GPIO_OType = GPIO_OType_PP; // GPIO_PuPd_UP
   GPIO_Init(GPIOA, &leds_init_structure);
   GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);

   return 0;
}


static int configure_timers(void)
{
   /* Timer  */
   TIM_TimeBaseInitTypeDef timer_init_structure;
   /* Initialize peripheral clock */
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   /* Initialize timer */
   timer_init_structure.TIM_Prescaler     = 8400;  /* Scale value to microseconds */
   timer_init_structure.TIM_CounterMode   = TIM_CounterMode_Up;
   timer_init_structure.TIM_Period        = 10000;   /* Gives us a second interval */
   timer_init_structure.TIM_ClockDivision = TIM_CKD_DIV1; /* Tell timer to divide clocks */
   timer_init_structure.TIM_RepetitionCounter = 0;
   TIM_TimeBaseInit(TIM2, &timer_init_structure);
   /* Start timer */
   TIM_Cmd(TIM2, ENABLE);

   return 0;
}




int main(void)
{ 


   SetSysClockTo84();

   uint32_t timer_value = 0;
   configure_leds();
   configure_timers();


   while(1)
   {
      timer_value = TIM_GetCounter(TIM2);

      if (timer_value == 10000)
      {
         GPIO_ToggleBits(GPIOA, GPIO_Pin_8);

      }

      
   }


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
