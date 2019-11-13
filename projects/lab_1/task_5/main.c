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

   uint32_t flag = 0;
   int HSEStartUpStatus;

   GPIO_ResetBits(GPIOA,GPIO_Pin_8 );
   delay(5000000);
   GPIO_SetBits(GPIOA, GPIO_Pin_8 );
   while (1)
   {

      int state = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0);
      if (!state)
      {
         if (flag == 1)
         {
            RCC_DeInit();
            RCC_HSICmd(ENABLE);

            RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

            while (RCC_GetSYSCLKSource() != 0x00);

            flag = 0;





         }

         else if (flag == 0 )
         {
            RCC_DeInit();
            RCC_HSEConfig( RCC_HSE_ON);

            HSEStartUpStatus = RCC_WaitForHSEStartUp();

            if (HSEStartUpStatus == SUCCESS)
            {

               RCC_SYSCLKConfig(RCC_SYSCLKSource_HSE);

               while (RCC_GetSYSCLKSource() != 0x04);

               flag = 1;
             /*  for (int i = 0; i < 10;i++)
               {
               GPIO_ResetBits(GPIOA,GPIO_Pin_9 );
               delay(10000000);
               GPIO_SetBits(GPIOA, GPIO_Pin_9 );
               }*/

            }
         }

      }

      GPIO_ResetBits(GPIOA,GPIO_Pin_10 );
      delay(100000);
      GPIO_SetBits(GPIOA, GPIO_Pin_10 );
      delay(100000);
   }
}




