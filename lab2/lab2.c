//Lab2 Spring 2015
//Vincent Chan
//RedID 815909699

#include <stdio.h>
typedef unsigned int uint;

//Function prototypes
int checkBit(uint u, uint bitNum);
void setBit(uint*u, uint bitNum);
int countOnes(uint u);

/**Main function******************************************/
/*                                                      **/
int main() {
  uint xxx, bitNumber;

  printf("\n Enter decimal integer xxx:");
  scanf("%u", &xxx);
  printf("\n xxx in decimal: %u", xxx);
  printf("\n xxx in hex: %x", xxx);

  //Testing countOnes
  printf("\n number of ones in xxx: %d", countOnes(xxx));
  
  //Test checkBit
  printf("\n Enter bit to check:");
  scanf("%u", &bitNumber);
  printf("\n Bit %d is %d", bitNumber, checkBit(xxx, bitNumber));
  printf("\n Enter bit to check:");
  scanf("%u", &bitNumber);
  printf("\n Bit %d is %d", bitNumber, checkBit(xxx, bitNumber));
  
  //Test setBit
  printf("\n Enter bit to set:");
  scanf("%u", &bitNumber);
  printf("\n setting bit %d of xxx", bitNumber);
  setBit(&xxx, bitNumber);
  printf("\n xxx in hex: %x", xxx);
  printf("\n");
  
  return 0;
} //End main()
/*                                                      **/ 
/**Main function******************************************/


/**Functions**********************************************/
/*                                                      **/ 
//This will check the bit of the specified bit position
//returns 0 if bitposition is larger than 32
int checkBit(uint u, uint bitNum) {
  if(bitNum>32 || bitNum<=0) return 0;
  return (u>>bitNum-1)%2;
} //End checkBit()

//This will set the bit of at the specified position to 1.
//returns if the bitNum is larger than 32.
void setBit(uint *u, uint bitNum) {
  if(bitNum>32 || bitNum<=0) return;
  *u |= 1<<bitNum-1;
} //End setBit()

//Counts the number of ones and returns the count.
int countOnes(uint u) {
  int count = 0;
  while(u!=0) {
    u &= u-1;
    count++;
  }
  return count;
} //End countOnes()
/*                                                      **/ 
/**Functions**********************************************/

/***************************************
 * Simplicty
 *        is
 *          Love
 ***************************************/
