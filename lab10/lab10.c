/**************
 * Spring 2015 Lab 10
 * Vincent Chan
 * RedID815909699
 **************/

/**DECLARATIONS*************************/
/**                                   **/
#include <STM32F0xx.h>
#include <math.h>
#include "lib.h" 

#define START_CONV      ADC1->CR |= (1<<2);
#define CONVERTING      ADC1->CR &  (1<<2)
#define BUTPRESS        GPIOA->IDR & (1<<0)

int debounce = 0;
int isOn = 1;
int time = 0;
uint16_t freq = 0;
uint16_t cnt = 0;

void init();
void delay(int ms);
/**                                   **/
/***************************************/

/**Main*********************************/
/**                                   **/
int main() {
  init();
  START_CONV;

  while(666) {
    if(isOn) {
      while(CONVERTING);
      freq = (ADC1->DR * .49) + 100; //Scaling to be 100 - 2000 Hz
			while(TIM1->CNT > (TIM1->ARR*.80));
      speakerOn(freq, 50, 50);
			delay(15);
      START_CONV;
      
    }
    else speakerOff();
  }
}
/**                                   **/
/***************************************/

/**FUNCTIONS****************************/
/**                                   **/
/* Initalize the system. To be run on startup */
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

/* Delays by the specified millisecond count */
void delay(int ms) {
  time = ms;
  while(time>0);
} //End delay()
/**                                   **/
/***************************************/

/**INTERRUPT****************************/
/**                                   **/
/* The interrupt handles debouncing
 * and delay countdowns */
void SysTick_Handler() {
  if(BUTPRESS) {
    if(debounce<=0) isOn^=1;
    debounce = 7;
  }
  else debounce--;
  time--;
} //End SysTick_Handler()  
/**                                   **/
/***************************************/

/********************************
 * WE REJECT:
 *  Kings, presidents, and voting.
 * WE BELIEVE IN:
 *  Rough consensus and running code.
 *  *  *  *  *  *  *  *  *  *  */
