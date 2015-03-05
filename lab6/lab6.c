/**************
 * Spring 2015 Lab 6
 * Vincent Chan
 * RedID815909699
 **************/

/**Includes and declarations*************/
/**                                    **/
#include <STM32F0xx.h>

/*Led and button usages*/
#define LED8 8 //Blue Led
#define LED9 9 //Green Led
#define BUT 0  //Button

/*Variable declarations*/
volatile uint32_t msTick = 0;
uint32_t blinkRate=1;
int validPress=0;

/*Prototype functions*/
void Init();                    //Ln. 50
void SysTick_Handler();         //Ln. 65
uint32_t butPress();            //Ln. 72
void delay(uint32_t);           //Ln. 90
/**                                    **/
/****************************************/

/**Main**********************************/
/**                                    **/
int main(void) {
  /*Initialize the system.*/
  Init();

  /*This is the main function,
   * which will turn the blue LED on
   * and off, according to the current
   * blinkRate. blinkRate is modified by
   * the interrupt.
   */
  while (1) {
    GPIOC->BSRR |= (1<< LED8);
    delay(1000/(blinkRate*2));
    GPIOC->BRR |= (1<< LED8);
    delay(1000/(blinkRate*2));
  }
} //End main()
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
  msTick--;
  validPress--;

  /*This is what will happen when
   * the button is pressed.
   * This includes a debouncer. */
  if(butPress()) {
    GPIOC->BSRR |= (1<< LED9);
    if(validPress<0) {
      (blinkRate==10)?blinkRate=1 : blinkRate++;
      /*Gives the button a 10 ms debounce*/
      validPress=10;
    }
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
  msTick = time;
  while(msTick>0);
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
