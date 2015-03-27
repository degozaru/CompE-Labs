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

int debounce = 0;
int newNote, pressedNum;
int scancode, note;
int startKey = 60;
float frequency;

void init();
int updateNotes();
int getNum();
void playNote(int scan);
void SysTick_Handler();
/**                                   **/
/***************************************/

/**Main Function************************/
/**                                   **/
int main() {
  init();
  while(666) {
    scancode = butPress();
    if(scancode==8) startKey = updateNotes();
    else if(scancode) { 
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

int getNum() {
  while(scancode>12||scancode%4==0) {
    scancode = butPress();
    if(scancode==15) return -1;
    if(scancode==14) return -2;
  }
  return scancode-(scancode/4);
} //End getNum()

void playNote(int scan) {
  (scan>8)?scan-=2:scan--;
  note = startKey + (scan*2);
  frequency = pow(2.0, ((float)note-69.0)/12.0) * 440.0;
  speakerOn(frequency, 50, 50);
} //End playNote()
/**                                   **/
/***************************************/


/**Systick******************************/
/**                                   **/
void SysTick_Handler() {
  if(!butPress()) debounce--;
} //End SysTick_Handler()
/**                                   **/
/***************************************/

