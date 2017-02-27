/*
 * max7219.c
 *
 * Created: 7/04/2015 10:34:41 AM
 *  Author: Samuel
 */ 
#define F_CPU 4000000UL
#include <util/delay.h>
#include <stdint.h>
#include "max7219.h"

//uint8_t circShift8(uint8_t input);

/* Transfer data out to the MAX7219
   set Load LOW
   transfer ADDRESS (MSB first)
   transfer DATA	(MSB first)
   set Load HIGH 	*/
void 
maxOut(uint8_t address, uint8_t dataOut) {
	
		int8_t i;		
		MAX_PORT &= ~_BV(MAX_LOAD_PIN);
		// Load ADDRESS
		for(i = 7; i >= 0; i--) {
				if(address & (1<<i)) {
						MAX_PORT |= _BV(MAX_DATA_PIN);
				} else {
						MAX_PORT &= ~_BV(MAX_DATA_PIN);
				}
				// Toggle clock to load data
				MAX_PORT |= _BV(MAX_CLOCK_PIN);
				MAX_PORT &= ~_BV(MAX_CLOCK_PIN);
				//_delay_ms(500);
				//PORTD &= ~_BV(PD0);
				//_delay_ms(500);
				//PORTD |= _BV(PD0);
		}
			
		
		// Load DATA
		for(i = 7; i >= 0; i--) {
				if(dataOut & (1<<i)) {
						MAX_PORT |= _BV(MAX_DATA_PIN);
				} else {
						MAX_PORT &= ~_BV(MAX_DATA_PIN);
				}
				// Toggle clock to load data
				MAX_PORT |= _BV(MAX_CLOCK_PIN);
				MAX_PORT &= ~_BV(MAX_CLOCK_PIN);
		}
		MAX_PORT |= _BV(MAX_LOAD_PIN);
}

/* Initialises the max7219 by 
   disabling Shutdown Mode,
   disabling Display Test Mode,
   disabling Decoding for all digits and
   setting the Scan Limit to all digits  */
void
maxInit(void) {
		MAX_PORT |= _BV(MAX_LOAD_PIN) | _BV(MAX_DATA_PIN) | _BV(MAX_CLOCK_PIN);
		
		maxOut(0x0C, 0x01); // Shutdown
		maxOut(0x0F, 0x00); // Display Test
		maxOut(0x09, 0x00); // Decoding
		maxOut(0x0B, 0x07); // Scan Limiting
		
			
		
}

// Clears the entire LED display
void
clearDisplay(void) {
		uint8_t i = 0x01;
		while(i++ <= 8) {
				maxOut(i, 0x00);
		}
}

/* Sets the intensity of the display.
   intensity is any integer between 0 and 15,
   with 0 being lowest and 15 being highest brightness */
void setIntensity(uint8_t intensity) {
		//maxOut(0x0A, (intensity = (intensity > 15) ? 15 : intensity));
		if(intensity > 15) {
				intensity = 15;
		}		
		maxOut(0x0A, intensity);
}

void
maxDisplay(uint64_t display) {
	uint8_t digit, data;
	
	for(digit = 1; digit <= 8; digit++) {
		data = (uint8_t)(display >> (64 - (digit * 8)));		
		//data = circShift8(data);
		maxOut(digit, data);
	}
} 

/* 
uint8_t
circShift8(uint8_t input) {
	if(input & 0b00000001) {
		input >>= 1;
		input |= 0b10000000;
	} else {
		input >>= 1;
		input &= 0b01111111;
	}
	
	return input;
}
}*/