/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes -------------------------------------------------------------*/
#include "main.h"

/* Private variables ----------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t BlinkSpeed = 0;

/**Main************************************/
/*                                        */
int main(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  
  /* Initializing everything*/
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
   
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 1;
  STM_EVAL_LEDOn(LED4);
  
  while(1)
  {  
    /* Check if the user button is pressed */
    if(STM_EVAL_PBGetState(BUTTON_USER)== SET)
    {
      /* Turn on both leds if button is pressed */
      STM_EVAL_LEDOn(LED4);
      STM_EVAL_LEDOn(LED3);
      
      /* Increment the blink speed counter */
      BlinkSpeed++;
      
      /*Reset the speed on the 6th cycle*/
      if(BlinkSpeed == 6)
      {  
        BlinkSpeed = 1;
      }
    
      /* Wait for the user to release the button*/
      while(STM_EVAL_PBGetState(BUTTON_USER)== SET)
        {/*Do nothing*/}
      
      /* resync the LED so they are blinking opposites*/
      STM_EVAL_LEDOff(LED3);
    }
    
    /*Cycle through*/
    STM_EVAL_LEDToggle(LED3);
    STM_EVAL_LEDToggle(LED4);
    Delay(1000/(BlinkSpeed*2));
  }
}
/*                                        */
/******************************************/

/********************
/* Theres that moment, you know...
/*   When the whole world fades away,
/*      And it's just you and your mod.
/*      And the mod is the world.
/*************************************/


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 1 ms.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
