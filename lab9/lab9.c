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

int scancode = 0;
int64_t debounce = 0;
int newNote, pressedNum;
int startKey = 60;
float frequency;

void init();                    //Ln. 46
int updateNotes();              //Ln. 64
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
    scancode = butPress();
    if(scancode==8) startKey = updateNotes();
    else if(butPress() && scancode) { 
			playNote(scancode);
			while(butPress()==scancode);
		}
		else speakerOff(); 
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
  initPin('C', 8, OUTPUT);
  SysTick_Config(SystemCoreClock/1000);
} //End init()
/**                                   **/
/***************************************/

/**Functions****************************/
/**                                   **/
/* Updates the pitch,
 * Enter the pitch number
 * Pound to exit update mode.*/
int updateNotes() {
  newNote=0;
  pinHigh('C', 8);
  while(666) {
    if(butPress()&&debounce<=0) {
      pressedNum = getNum();
      if(pressedNum==-1) break;
      else newNote = (newNote*10) + pressedNum;
      debounce = 7;
    }
  }
  pinLow('C', 8);
  return newNote;
} //End updateNotes()

/* Plays the note corresponding to the scancode.
 * the note is the following formula:
 * two to the power of (note - 69)/12
 * times 440 Hz. */
void playNote(int scan) {
  (scan>8)?scan-=2:scan--;
  frequency = pow(2.0, ((float)(startKey + (scan*2))-69.0)/12.0) * 440.0;
  speakerOn(frequency, 50, 50);
} //End playNote()

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
} //End SysTick_Handler()
/**                                   **/
/***************************************/

