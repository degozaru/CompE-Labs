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
#include <STM32F0xx.h>

/*Pin mode definitions*/
#define INPUT           0
#define OUTPUT          1
#define ALTMODE         2
#define ANALOG          3

/*Bit address for hardware*/
#define HEXPAD          0
#define SPEAKER         16
#define BUT             0

/*Basic port/GPIO functions*/
void portEnable(char port);
void pinHigh(char port, int pin);
void pinLow(char port, int pin);
void initPin(char port, int pin, int mode);

/*Hexpad*/
void initHex();
uint8_t butPress();

/*Speakers*/
void initSpeaker();
void speakerOn(uint16_t period, uint16_t compare1, uint16_t compare2);
void speakerOff();
void initSpeaker2();
void speaker2On(uint16_t period);
void speaker2Off();

/*USART comms*/
void serialStart(uint16_t baud);
uint8_t getChar();
int putChar(uint8_t txChar);

/*Clock*/
void clockStart();

/*User Pushbutton*/
void initButton();
uint32_t butPress();

/*Photocell ADC*/
void initPhotocell();
void startConv();
uint16_t getConv();

#endif
