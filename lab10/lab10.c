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

#define START_CONV      ADC->CR |= (1<<2);
#define CONVERTING      ADC->CR &  (1<<2);

void init();

int main() {
  init();
  START_CONV;

  while(666) {
    if(!CONVERTING) {
      speakerOn(ADC->DR, 50, 50);
      START_CONV;
    }
}

void init() {
  portEnable('A');
  initPin('A', 1, ANALOG);
  initSpeaker();
  
  RCC->APB2ENR |= (1<<9); //Enable ADC
  ADC->CR |= (1<<0);
  ADC->CHSELR |= (1<<1);
}
  
  

