#include "lib.h"

/* This will enable the specified port. */
void portEnable(char port) {
  RCC->AHBENR |= (1<<(17+(port-'A')));
} //End portEnable();

/*This will set the pin to output 1.*/
void pinHigh(char port, int pin) {
  switch(port) {
    case 'A':
      GPIOA->BSRR |= (1<<pin);
    case 'B':
      GPIOB->BSRR |= (1<<pin);
    case 'C':
      GPIOC->BSRR |= (1<<pin);
    case 'D':
      GPIOD->BSRR |= (1<<pin);
    case 'E':
      GPIOE->BSRR |= (1<<pin);
    case 'F':
      GPIOF->BSRR |= (1<<pin);
} //End pinHigh()


/*This will reset the pin to output 0.*/
void pinLow(char port, int pin) {
  switch(port) {
    case 'A':
      GPIOA->BRR |= (1<<pin);
    case 'B':
      GPIOB->BRR |= (1<<pin);
    case 'C':
      GPIOC->BRR |= (1<<pin);
    case 'D':
      GPIOD->BRR |= (1<<pin);
    case 'E':
      GPIOE->BRR |= (1<<pin);
    case 'F':
      GPIOF->BRR |= (1<<pin);
} //End pinLow()
