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

/*Basic port/GPIO functions*/
void portEnable(char port);
void pinHigh(char port, int pin);
void pinLow(char port, int pin);
void initPin(char port, int pin, int mode);

/*Init hexpad*/
void initHex();
uint8_t butPress();
#endif



