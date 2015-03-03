/***************************************************************** 
 *  Vincent Chan Spring 2015 CompE275
 *
 *****************************************************************/
#include <STM32F0xx.h>

/*----------------------------------------------------------------------------
  Function that initializes button and gpio
 *----------------------------------------------------------------------------*/
void Init(void) {

  RCC->AHBENR  |= ((1UL << 17) );               /* Enable GPIOA clock         */

  GPIOA->MODER    &= ~((3UL << 2*0)  );         /* PA.0 is input              */
  GPIOA->OSPEEDR  &= ~((3UL << 2*0)  );         /* PA.0 is Low Speed          */
  GPIOA->PUPDR    &= ~((3UL << 2*0)  );         /* PA.0 is no Pull up         */
  
  
  RCC->AHBENR |= (1UL << 19);  
  GPIOC->MODER  &= ~((3UL << 2 * 8) | (3UL << 2 * 9));
  GPIOC->MODER  |=  ((1UL << 2 * 8) | (1UL << 2 * 9));
  GPIOC->OTYPER &= ~((1UL <<     8) | (1UL <<     9));
}

/*----------------------------------------------------------------------------
  Function that read Button press
 *----------------------------------------------------------------------------*/
uint32_t BTN_Press(void) {
 return (GPIOA->IDR & (1UL << 0));
}

void delay(uint32_t);

uint32_t clockRate = 1;

int main(void)
{
  Init();
  
  while(1) {
    GPIOC->BSRR = (1<<8);
    delay(500/clockRate);
    GPIOC->BSRR = (1<<24);
    delay(500/clockRate);
    
    if(BTN_Press()) {
      GPIOC->BSRR = (1<<9);
      (clockRate==10)?clockRate=1 : clockRate++;
      while(BTN_Press()) {/*do nothing*/}
      GPIOC->BSRR = (1<<25);
    } 
  }
  return 0;
}

void delay(uint32_t ms) {
  ms*=9500;
  while(ms>0) ms--;
}
