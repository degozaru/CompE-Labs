/**************
 * Spring 2015 Lab 10
 * Vincent Chan
 * RedID815909699
 **************/

/**Includes and declarations************/
/**                                   **/
#include <STM32F0xx.h>
#include <math.h>
#include "lib.h" 

#define START_CONV      ADC1->CR |= (1<<2);
#define CONVERTING      ADC1->CR &  (1<<2)
#define BUTPRESS 				GPIOA->IDR & (1<<0)

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
  initPin('A', 1, ANALOG);
	initPin('A', 0, INPUT);
  initSpeaker();
	SysTick_Config(SystemCoreClock/1000);
  
  RCC->APB2ENR |= (1<<9); //Enable ADC
  ADC1->CR |= (1<<0);
  ADC1->CHSELR |= (1<<1);
}
  
void SysTick_Handler() {
	if((BUTPRESS)) {
		if(debounce<= 0) isOn ^= 1;
		debounce = 7;
	}
	else debounce--;
	time--;
}

void delay(int ms) {
	time = ms;
	while(time > 0);
}
