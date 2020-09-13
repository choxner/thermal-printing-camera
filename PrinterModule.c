#include <avr/io.h>	// control pins
#include <util/delay.h>	// enable delays
#include "PrinterModule.h"	// respective header
#include "SPI.h"	// my SPI methods

void pinAssignments(void)	{
	DDRD |= (111111 << DDD2);
	DDRB |= (111 << DDB0);
	DDRC |= (111 << DDC0);
	// sets all to outputs
}

void lineByLine()	{
	
	pinAssignments();
	PORTC |= (1 << PORTC2); // turns on all AEO
	stepperEnable(true);
	spiConfig("printer");
	
	for (int i = 1; i <= frameHeight; i++)	{
		
		for (int j = 1; j <= 5; j++)	{
			
			_delay_us(0.03); // t setup DI
			spiTransfer(lineData[i][j]);
			_delay_us(1.01); // t hold DI and t setup LAT
			
			latch(false);
			_delay_us(1); // t w LAT
			latch(true);
			
			_delay_us(3); // t setup STB
			strobe(j,true);
			phaseStepping(i, j);
			strobe(j,false);

		}

	}
	
	stepperEnable(false);
	PORTC &= ~(1 << PORTC2);	// turn off aeo
}

void latch(bool latchEnable)	{
	if (latchEnable)	{
		PORTD |= (1 << PORTD2);
		// set enable pin to high
	}	else	{
		PORTD &= ~(1 << PORTD2);
		// set enable pin to low
	}
}

void strobe(int pinNumber, bool strobeEnable)	{
	// pins are set to 0 when the strobe is on
	if (strobeEnable)	{
		switch (pinNumber){
			case 1:		// STB1	
				PORTB &= ~(1 << PORTB0);
				// disable pin
			break;
			case 2:		// STB2
				PORTB &= ~(1 << PORTB1);
			break;
			case 3:		// STB3
				PORTB &= ~(1 << PORTB2);
			break;
			case 4:		// STB4
				PORTC &= ~(1 << PORTC0);
			break;
			case 5:		// STB5
				PORTC &= ~(1 << PORTC1);
			break;
		}

	}	else	{
		switch (pinNumber){
			case 1:		// STB1	
				PORTB |= (1 << PORTB0);
				// enable pin
			break;
			case 2:		// STB2
				PORTB |= (1 << PORTB1);
			break;
			case 3:		// STB3
				PORTB |= (1 << PORTB2);
			break;
			case 4:		// STB4
				PORTC |= (1 << PORTC0);
			break;
			case 5:		// STB5
				PORTC |= (1 << PORTC1);
			break;
		}
	}

	
}

void stepperEnable(bool motorEnable)	{
	if (motorEnable)	{
		PORTD |= (1 << PORTD3);
		// set enable pin to high
	}	else	{
		PORTD &= ~(1 << PORTD3);
		// set enable pin to low
	}
}


void driveStep(int stepNumber) {
	switch (stepNumber)	{
		case 0:
			PORTD = (0000 << DDD4);
			// stop
		break;
		case 1:
			PORTD = (0101 << DDD4);
			// values from datasheet for the stepper IC
			// order: IN4, IN3, IN2, IN1
		break;
		case 2: 
			PORTD = (0100 << DDD4);
		break;
		case 3:
			PORTD = (0110 << DDD4);
		break;
		case 4:
			PORTD = (0010 << DDD4);
		break;
		case 5:
			PORTD = (1010 << DDD4);
		break;
		case 6:
			PORTD = (1000 << DDD4);
		break;
		case 7:
			PORTD = (1001 << DDD4);
		break;
		case 8:
			PORTD = (0001 << DDD4);
		break;
	}

	_delay_ms()
	
	PORTD = (0000 << DDD4);
	// stop motors
}

void phaseStepping(int lineNumber, int sectionNumber)	{
	
	if ((lineNumber % 2) != 0)	{
		
		switch (sectionNumber)	{
			case 1:
				driveStep(1);
			case 2:
				driveStep(2);
			break;
			case 3: 
				driveStep(3);
			break;
			case 4:
				driveStep(4);
			break;
		}

	}	else 	{
		
		switch (sectionNumber)	{
			case 1:
				driveStep(5);
			case 2:
				driveStep(6);
			break;
			case 3: 
				driveStep(7);
			break;
			case 4:
				driveStep(8);
			break;
		}
	}
}