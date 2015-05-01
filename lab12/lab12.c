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

int i;

/*Interrupt util*/
int64_t debounce = 0;
int64_t ms=0;

/*USART util*/
int buf[100] = {0x69, 0x6E, 0x63, 0x65, 0x6E, 
                  0x74, 0x20, 0x43, 0x68, 0x61, 0x6E};
int size = 11;


/*Hexpad utility variables*/
int scancode = 0, noteChange = 0,
    newNote = 0, startKey = 60
    prevNote = 0;
float frequency;

void init();                    //Ln. 46
void playNote(int scan);        //Ln. 82
void turnOff(int scan);
//void printNote(int on, int note, uint64_t mil);
int getNum();                   //Ln. 92
void SysTick_Handler();         //Ln. 109
/**                                   **/
/***************************************/

/**Main Function************************/
/**                                   **/
int main() {
  init();
  USART1->TDR = 0x56;
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
      speakerOn(scancode);
		else if(!butPress() && prevNote!=0)
      turnOff(scancode);

    /* Process USART */
    if(size)
      if(putChar(buf[0])){
        for(i=0; i<size-1; i++)
          buf[i] = buf[i+1];
        size--;
      }
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
  portEnable('B');
  initHex();
  initSpeaker();
  SysTick_Config(SystemCoreClock/1000);
  serialStart(9600);
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
  //printNote(1, startKey + scan, ms); 
} //End playNote()

/*Turns the note off*/
void turnOff(int scan) {
  prevNote=0;
  (scan>8)?scan-=2:scan--;
  speakerOff();
  //printNote(0, startKey+scan, ms);
} //End turnOff()

/* prints the note to the USART 
void printNote(int on, int note, uint64_t mil) {
  buf[size] = "Note ";
  size+=5;
  do {
    buf[size] = (note%10) - '0';
    size++;
    note/=10;
  } while(note);
  if(on) {
    buf[size] = " on ";
    size+=4;
  }
  else {
    buf[size] = " off ";
    size+=5;
  }
  while(mil) {
    buf[size] = (mil%10) - '0';
    size++;
    mil/=10;
  }
  buf[size] = " ms.";
  size+=4;
  buf[size] = 0x0D;
  buf[size+1] = 0x0A;
  size+=2
} //End printNote() */

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

