/**************
 * Spring 2015 Lab 11
 * Vincent Chan
 * RedID815909699
 **************/

/**DECLARATIONS*************************/
/**                                   **/
#include <STM32F0xx.h>
#include <math.h>
#include "lib.h" 

 int buf[25] = {0x69, 0x6E, 0x63, 0x65, 0x6E, 
                  0x74, 0x20, 0x43, 0x68, 0x61, 0x6E};
int size = 11;
int i;

void init();
/**                                   **/
/***************************************/

/**Main*********************************/
/**                                   **/
int main() {
  init();
	USART1->TDR = 0x56;
  while(666) {
    if(size)
      if(putChar(buf[0])){
        for(i=0; i<size-1; i++) {
          buf[i] = buf[i+1];
				}
				size--;
			}
    buf[size] = getChar();
    if(buf[size]!=0xFF) {
      if(buf[size]>0x60 && buf[size]<0x7B)
        buf[size] -= 0x20;
      if(buf[size]==0x0D || buf[size]==0x0A) {
        buf[size] = 0x0D;
        buf[size+1] = 0x0A;
        size++;
      }
      size++;
    }
	}
}                 
/**                                   **/
/***************************************/

/**FUNCTIONS****************************/
/**                                   **/
/* Initalize the system. To be run on startup */
void init() {
  portEnable('A');
  serialStart(9600);
} //End init()
/**                                   **/
/***************************************/

/********************************
 * The greatest pleasure in life
 * is doing what people say you can't do.
 *  *  *  *  *  *  *  *  *  *  */
