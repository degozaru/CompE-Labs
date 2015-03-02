/**************
 * Spring 2015 Lab 6
 * Vincent Chan
 * RedID815909699
 **************/

#include <STM32F0xx.h>

#define LED8 8
#define LED9 9
#define BUT 0

//Variable declarations
volatile uint32_t msTick = 0;

//Prototype functions
void delay(uint32_t);
void Init();
void SysTick_Handler();
uint32_t butPress();
void delay(uint32_t);

int main(void) {
  //Initialize the system.
  Init();

  while (1) {
    //turn on GPIOC 8 (blue LED)
    GPIOC->BSRR |= (1<< LED8);
    delay(1000);
    //turn off GPIOC 8
    GPIOC->BRR |= (1<< LED8);
  }
}

//This function will handle all initialization of the system.
void Init() {
  /*Configure the interrupt to run every millisecond*/
  RCC->AHBENR |= (1<<17);
  SysTick_Config(SystemCoreClock/1000);
  /*Configure 8th and 9th pin as output.*/
  RCC->AHBENR |= (1<<19);
  GPIOC->MODER |= (1<<LED8*2) | (1<<LED9*2);
  /*Configure button as input, and no pull up*/
  GPIOA->MODER &= ~(3<<BUT*2);
  GPIOA->OTYPER &= ~(3<<BUT*2);
} //End Init()

//This function is the interrupt function.
//This will happen every millisecond.
void SysTick_Handler() {
  msTick++;
  if(butPress()) {
    GPIOC->BSRR |= (1<< LED9);
    while(butPress());
    GPIOC->BRR |= (1<<LED9);
  }
} //End SysTick_Handler()

uint32_t butPress() {
  return (GPIOA->IDR & (1<<BUT));
}

void delay(uint32_t time) {
  time += msTick;
  while(msTick<=time);
  msTick=0;
}
