/****************************
 * CompE375 Spring 2015
 * Library
 *
 * By Vincent Chan
 *
 * This is a library that will consolidate all config.
 * It will be added onto as time goes on.
 * ***************************/
#ifndef LIBRARY_H
#define LIBRARY_H 

/*Pin mode definitions*/
#define INPUT           0
#define OUTPUT          1
#define ALTMODE         2

/*Bit address for hardware*/
#define HEXPAD          0
#define SPEAKER         16

/*Basic port/GPIO functions*/
void portEnable(char port);
void pinHigh(char port, int pin);
void pinLow(char port, int pin);
void initPin(char port, int pin, int mode);

/*Hexpad*/
int row, col;
void initHex();
uint8_t butPress();

/*Speakers*/
void initSpeaker();
void speakerOn(uint16_t period, uint16_t compare1, uint16_t compare2);
void speakerOff();

#endif


