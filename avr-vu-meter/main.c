/*
* main.c
*
* Created: 7/04/2015 10:34:32 AM
*  Author: Samuel
*/

#define F_CPU 4000000UL
#include <inttypes.h>
#include <util/delay.h>

#include "max7219.h"

int
main() {
	//uint64_t display = 0xFFFFFFFFFFFFFFFF;
	uint8_t digit;
	
	maxOut(0x0F, 0x01); // display test
	_delay_ms(2000);
	maxOut(0x0F, 0x00); // display test
	
	maxInit();	
	clearDisplay();
	setIntensity(10);
	
	_delay_ms(1000);
	
	DDRD |= _BV(PD0);
	PORTD |= _BV(PD0);
	_delay_ms(500);
	PORTD &= ~_BV(PD0);
	_delay_ms(1500);
	
	while(1) {
		for(digit = 1; digit <= 8; digit++) {
			//PORTD |= _BV(PD0);
			maxOut(1, 0x0F);
			PORTD |= _BV(PD0);
			_delay_ms(250);
			//PORTD &= ~_BV(PD0);
			maxOut(1, 0x00);
			PORTD &= ~_BV(PD0);
			_delay_ms(250);
		}
		
		//PORTB |= _BV(PB3);
		//_delay_ms(500);
		//PORTB &= ~_BV(PB3);
		//_delay_ms(500);
		
		
	}
	
	
}