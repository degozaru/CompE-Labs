/**************
 * Spring 2015 Lab 6
 * Vincent Chan
 * RedID815909699
 **************/

/**Includes and declarations*************/
/**                                    **/
#include <STM32F0xx.h>

#define LED8 8
#define LED9 9
#define BUT 0

//Variable declarations
volatile uint32_t msTick = 0;
uint32_t blinkRate=1;
uint32_t validPress=0;

//Prototype functions
void Init();                    //Ln. 45
void SysTick_Handler();         //Ln. 58
uint32_t butPress();            //Ln. 70
void delay(uint32_t);           //Ln. 75
/**                                    **/
/****************************************/

/**Main**********************************/
/**                                    **/
int main(void) {
  //Initialize the system.
  Init();

  while (1) {
    GPIOC->BSRR |= (1<< LED8);
    delay(1000/blinkRate);
    GPIOC->BRR |= (1<< LED8);
    delay(1000/blinkRate);
  }
}
/**                                    **/
/****************************************/

/**Functions******************************/
/**                                    **/
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
  /*Increase ms tick and debouncer tick.*/
  msTick++;
  validPress--;

  //This is what will happen when
  //the button is pressed.
  //This includes a debouncer.
  if(butPress() && validPress<0) {
    GPIOC->BSRR |= (1<< LED9);
    /*Gives the button a 10 ms debounce*/
    validPress=10;
    (blinkRate==)?blinkRate=1 : blinkRate++;
    while(butPress());
    GPIOC->BRR |= (1<<LED9);
  }
} //End SysTick_Handler()

//Returns 1 if button is pressed
uint32_t butPress() {
  return (GPIOA->IDR & (1<<BUT));
} //End butPress()

//This will delay by specified milliseconds
void delay(uint32_t time) {
  time += msTick;
  while(msTick<=time);
  msTick=0;
} //End delay()
/**                                    **/
/****************************************/

/**************
 * That brain of mines
 *  is something more than merely mortal
 *    As time will show.
 *  
 *  Ada Lovelace
 **************/
