/*
 * max7219.h
 *
 * Created: 7/04/2015 10:34:50 AM
 *  Author: Samuel
 */ 

#include <avr/io.h>
#include <inttypes.h>


#ifndef MAX7219_H_
#define MAX7219_H_

#define MAX_PORT PORTD
#define MAX_LOAD_PIN PD3
#define MAX_CLOCK_PIN PD2
#define MAX_DATA_PIN PD5

void maxInit();
void maxOut(uint8_t, uint8_t);
void setIntensity(uint8_t);
void clearDisplay();
void maxDisplay(uint64_t);

#endif /* MAX7219_H_ */