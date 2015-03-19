/**************
 * Spring 2015 Lab 8
 * Vincent Chan
 * RedID815909699
 **************/

/**Includes and declarations*************/
/**                                    **/
#include <STM32F0xx.h>

/*Hexpad and speaker usages*/
#define HEXPAD 0
#define SPEAKER 16

/*Variable declarations*/
int row, col; 
uint16_t period;

/*Prototype functions*/
void Init();                    //Ln. 46
uint8_t butPress();             //Ln. 59
/**                                    **/
/****************************************/

/**Main**********************************/
/**                                    **/
int main(void) {
  /*Initialize the system.*/
  Init();
  while(666) {
    if(butPress()) {
      period = (SystemCoreClock / (50*butPress())) - 1;
      TIM1->ARR = period
      TIM1->CCR1 = (50 * period / 100);
      TIM1->CCR2 = (10 * period / 100);
      RCC->AHBENR |= (1<<17);
    }
    else RCC->APB2ENR &= ~(1<<11);
  }
} //End main()
/**                                    **/
/****************************************/

/**Functions******************************/
/**                                     **/
//This function will handle all initialization of the system.
void Init() {
  /*Clock enable port C and then enable hexpad*/
  RCC->AHBENR |= (1<<19);
  GPIOC->MODER |= (0x55<<HEXPAD); 
  GPIOC->PUPDR |= (0x55<<(HEXPAD+4)*2);

  /*Clock enable port A, set up speaker pins*/
  RCC->AHBENR |= (1<<17);
  GPIOA->MODER |= (0xA<<SPEAKER);
  GPIOA->AFR[1] |= (0x22);
} //End Init()

//Returns the scancode if button is pressed
//Scancode: 4(row) + col + 1
//returns 0 if nothing is pressed
uint8_t butPress() {
	GPIOC->BSRR |= (0xf<<(HEXPAD));
	for(row=0; row<4; row++) {
    GPIOC->BRR |= (1<<(HEXPAD+row));
    for(col=0; col<4; col++)
      if(~GPIOC->IDR & (1<<((HEXPAD+4)+col))) {
        GPIOC->BSRR |= (1<<(HEXPAD+row));
        return (row*4) + col + 1;
      }
    GPIOC->BSRR |= (1<<(HEXPAD+row));
  }
  return 0;
} //End butPress()
/**                                    **/
/****************************************/

/**************
 * Your code is shit
 *  Your argument is shit
 *  -Linus Torvalds
 **************/
