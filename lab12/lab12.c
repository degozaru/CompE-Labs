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

/*Interrupt debouncer*/
int64_t debounce = 0;
int64_t ms=0;

/*Hexpad utility variables*/
int scancode = 0, noteChange = 0,
    newNote = 0, startKey = 60
    prevNote = 0;
float frequency;

void init();                    //Ln. 46
void playNote(int scan);        //Ln. 82
int getNum();                   //Ln. 92
void SysTick_Handler();         //Ln. 109
/**                                   **/
/***************************************/

/**Main Function************************/
/**                                   **/
int main() {
  init();
  while(666) {
    /* Process hexpad */
    scancode = butPress();
    if(scancode==8) noteChange=1;
    else if(noteChange) {
      if(getNum() == -1) {
        noteChange = 0;
        startKey = newNote;
        newNote = 0;
      }
      else if(scancode && butPress() && debounce<=0) {
        newNote = (newNote*10) + getNum();
        debounce = 7;
      }
    }
    else if(butPress() && scancode && prevNote!=scancode)
			playNote(scancode);
		else if(!butPress() && prevNote!=0)
      turnOff(prevNote);
  }
}
/**                                   **/
/***************************************/

/**Init function************************/
/**                                   **/
/*Initializes the system.
 * Enabled Ports: A, C, and TIM1.
 * Utility used: Hexpad and Speaker
 * Pins used: 8 for LED. 
 * Interrupt speed: 1 ms */
void init() {
  portEnable('A');
  portEnable('C');
  initHex();
  initSpeaker();
  SysTick_Config(SystemCoreClock/1000);
} //End init()
/**                                   **/
/***************************************/

/**Functions****************************/
/**                                   **/
/* Plays the note corresponding to the scancode.
 * the note is the following formula:
 * two to the power of (note - 69)/12
 * times 440 Hz. */
void playNote(int scan) {
  prevNote=scan;
  (scan>8)?scan-=2:scan--;
  frequency = pow(2.0, ((float)(startKey + (scan*2))-69.0)/12.0) * 440.0;
  speakerOn(frequency, 50, 50);
  printNote(1, startKey + scan, ms); 
} //End playNote()

/*Turns the note off*/
void turnOff(int scan) {
  prevNote=0;
  (scan>8)?scan-=2:scan--;
  speakerOff();
  printNote(0, startKey+scan, ms);
} //End turnOff()

/* prints the note to the USART */
void printNote(int on, int note, uint64_t mil) {
}

/* Gets the true number of button press
 * to the corresponding scancode. */
int getNum() {
	scancode= butPress();
  while(scancode>12||scancode%4==0) {
    scancode = butPress();
    if(scancode==15) return -1;
    if(scancode==14) return 0;
  }
  return scancode-(scancode/4);
} //End getNum()
/**                                   **/
/***************************************/


/**Systick******************************/
/**                                   **/
/* Systick for debouncing */
void SysTick_Handler() {
  if(!butPress()) debounce--;
  ms++;
} //End SysTick_Handler()
/**                                   **/
/***************************************/

