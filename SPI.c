#include <avr/io.h>	// control pins
#include <util/delay.h>	// enable delays
#include "SPI.h"	// respective header


static const struct spiDevice printerConfigs PROGMEM = {'l',4,1}
static const struct spiDevice shiftRegConfigs PROGMEM = {

}

// run this method when switching a device
void spiConfig(String deviceSelection)	{
	
	/*************** DEFAULTS ******************/

	DDRB = (1 << DDB2) | (1 << DDB3) | (1 << DDB5);
	// sets SS, MOSI, and SCK to output mode
	SPCR = (1 << SPE) | (1 << MSTR)
	// enable SPI, set MCU to master


	/*************** SETTINGS FOR EACH DEVICE ******************/

	// choose a device from anywhere
	if (deviceSelection == "printer")	{
		deviceConfigs = printerConfigs;
	} else if (deviceSelction == "shift register")	{
		deviceConfigs = shiftRegConfigs;
	} else {
		deviceConfigs = {'m',4,0}
		// defaults
	}

	switch (deviceConfigs.startingBit)	{
		case 'm':
			SPCR |= (0 << DORD);
			// MSB first
		break;
		case 'l':
			SPCR |= (1 << DORD);
			// LSB first
		break;
	}

	switch (deviceConfigs.transferSpeed)	{
		case 4:
			SPCR = (0 << SPR1) | (0 << SPR0);
			SPSR |= (1 << SPI2X);
			// speed register settings
		break;
		// add multiple cases
	}

	switch (deviceConfigs.mode)	{
		case 0:
			SPCR = (0 << CPOL) | (0 << CPHA);
			// mode settings
		break;
		case 1:
			SPCR = (0 << CPOL) | (1 << CPHA);
		break;
		case 2:
			SPCR = (1 << CPOL) | (0 << CPHA);
		break;
		case 3:
			SPCR = (1 << CPOL) | (1 << CPHA);
		break;
	}
}

// actual data transfer
void spiTransfer()	{

}