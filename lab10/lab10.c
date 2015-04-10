/**************
 * Spring 2015 Lab 9
 * Vincent Chan
 * RedID815909699
 **************/

/**Includes and declarations************/
/**                                   **/
#include <STM32F0xx.h>
#include <math.h>
#include "lib.h" 

#define START_CONV      ADC1->CR |= (1<<2);
#define CONVERTING      ADC1->CR &  (1<<2);
#define BUTPRESS        GPIOA->IDR & (1<<0)

int debounce = 0;
int isOn = 1;
int time = 0;

void init();
void delay(int ms);

int main() {
  init();
  START_CONV;

  while(666) {
    if(isOn) {
      speakerOn(ADC1->DR, 50, 50);
      START_CONV;
      delay(2);
    }
    else speakerOff();
  }
}

void init() {
  portEnable('A');

  /* Enable input pin, and button press */
  initPin('A', 1, ANALOG);
  initPin('A', 0, INPUT);

  /* Enable speaker */
  initSpeaker();
  
  /* Enable interrupt */
  SysTick_Config(SystemCoreClock/1000);
  
  /* ADC enable */
  RCC->APB2ENR |= (1<<9);
  ADC1->CR |= (1<<0);
  ADC1->CHSELR |= (1<<1);
} //End init()

void delay(int ms) {
  time = ms;
  while(time>0);
} //End delay()

void SysTick_Handler() {
  if(BUTPRESS) {
    if(debounce<=0) isOn^=1;
    debounce = 7;
  }
  else debounce--;
  time--;
} //End SysTick_Handler()  

