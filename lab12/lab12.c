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

/*LED util*/
int blueARR = 1, blueCNT = 0, blueO = 0;
int greenARR = 1, greenCNT = 0, greenO = 0;

/*Photocell util*/
int photoOn = 1;

/*Interrupt util*/
int64_t debounce = 0;
int64_t ms=0;

/*USART util*/
int buf[100] = {0x69, 0x6E, 0x63, 0x65, 0x6E, 
                  0x74, 0x20, 0x43, 0x68, 0x61, 0x6E};
int size = 11;
int getBuff = 0;
int numIndex = 0;


/*Hexpad utility variables*/
int scancode = 0, noteChange = 0,
    startKey = 60, newNote = 0,
    prevNote = 0;
float frequency;

void init();                    //Ln. 46
void playNote(int scan);        //Ln. 82
void turnOff();
void printNote(int on, int note, uint64_t mil);
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
    else if(butPress() && scancode) {
			debounce = 7;
			playNote(scancode);
		}
		else if(!butPress()) {
      turnOff();
		}
		

    /* Process USART */
    if(size)
      if(putChar(buf[0])){
        for(i=0; i<size-1; i++)
          buf[i] = buf[i+1];
        size--;
      }

   /* Process Photocell */ 
    if(photoOn) speaker2On(getConv());
    else speaker2Off();
    startConv();
			
		if(blueCNT>(60/(blueARR*2))) {
		if(blueOn) blueOff();
		else blueOn();
		blueO^=1;
		blueCNT = 0;
	}
	if(greenCNT>(60/(greenARR*2))) {
		if(greenOn) greenOff();
		else greenOn();
		greenO^= 1;
		blueCNT = 0;
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
  initSpeaker2();
  initPhotocell();
  initButton();
  startConv();
  initLed();
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
  if(scan>8) scan--;
	if(!prevNote) { 
		prevNote = scan;
		printNote(0, scan+startKey, ms);
	}
  frequency = pow(2.0, ((float)(startKey + (scan*2))-69.0)/12.0) * 440.0;
  speakerOn(frequency, 50, 50);
  //printNote(1, startKey + scan, ms); 
} //End playNote()

/*Turns the note off*/
void turnOff() {
	if(prevNote) {
		printNote(prevNote, prevNote+startKey, ms);
		prevNote = 0;
	}
  prevNote=0;
  speakerOff();
  //printNote(0, startKey+scan, ms);
} //End turnOff()

/* prints the note to the USART */
void printNote(int on, int note, uint64_t mil) {
  buf[size] = 'N';
	buf[size+1] = 'o';
	buf[size+2] = 't';
	buf[size+3] = 'e';
	buf[size+4] = ' ';
  size+=5;
	numIndex=size;
  do {
    for(i=size; i>numIndex; i--)
      buf[i] = buf[i-1];
    buf[numIndex] = (note%10) + '0';
    size++;
    note/=10;
  } while(note);
  if(on) {
    buf[size] = ' ';
    buf[size+1] = 'o';
    buf[size+2] = 'n';
    buf[size+3] = ' ';
    size+=4;
  }
  else {
    buf[size] = ' ';
    buf[size+1] = 'o';
    buf[size+2] = 'f';
    buf[size+3] = 'f';
    buf[size+4] = ' ';
    size+=5;
  }
  numIndex=size;
  do {
    for(i=size; i>numIndex; i--)
      buf[i] = buf[i-1];
    buf[numIndex] = (mil%10) + '0';
    size++;
    mil/=10;
  } while(mil);
  buf[size] = ' ';
  buf[size+1] = 'm';
  buf[size+2] = 's';
  size+=3;

  buf[size] = 0x0D;
  buf[size+1] = 0x0A;
  size+=2;
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
  if(!butPress() && !usrButPress()) debounce--;
  ms++;
	blueCNT++;
	greenCNT++;

  if(usrButPress() && debounce<=0) {
    photoOn ^= 1;
    debounce = 7;
  }
	
	getBuff = getChar();
	if(getBuff == 0x62) {
		blueARR++;
		if(blueARR==11) blueARR=1;
		buf[size] = 'b';
		size++;
		buf[size] = 0x0D;
		buf[size+1] = 0x0A;
		size+=2;
	}
	if(getBuff == 0x67) {
		greenARR++;
		if(greenARR==11) greenARR=1;
		buf[size] = 'g';
		size++;
		buf[size] = 0x0D;
		buf[size+1] = 0x0A;
		size+=2;
	}
	

	
 } //End SysTick_Handler()
/**                                   **/
/***************************************/
