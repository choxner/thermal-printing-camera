#include <stdint.h>	// bit and byte info
#include <util/twi.h>	// use i2c protocol
#include <util/delay.h>	// enable delays
#include "i2c.h"	// use .h counterpart

static void errorLed(void){
	DDRB |= 32; //make sure led is output
	while (1) { //wait for reset
		PORTB^=32;// toggle led
		_delay_ms(100);
	}
}

static void twiStart(void) {
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	// start TWI trnasmission
	while (!(TWCR & (1<<TWINT)));
	// wait for start to be transmitted
	if((TWSR & 0xf8) != TW_START) {
		errorLed();
	}
}

static void twiWriteByte(uint8_t DATA, uint8_t type) {
	TWDR = DATA;
	TWCR = _BV(TWINT) | _BV(TWEN);
	// clear interrupt
	while (!(TWCR & (1<<TWINT)));
	// wait for data to be transmitted
	if ((TWSR & 0xf8) != type) {
		errorLed();
	}
}

static uint8_t twiRead(uint8_t nack) {
	if (nack) {
		TWCR = _BV(TWINT) | _BV(TWEN);
		while ((TWCR & _BV(TWINT)) == 0)
		// wait for transmission
		if ((TWSR & 0xf8) != TW_MR_DATA_NACK) {
			errorLed();
		}
	}
	else {
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
		while ((TWCR & _BV(TWINT)) == 0)
		// wait for transmission
		if ((TWSR & 0xf8) != TW_MR_DATA_ACK) {
			errorLed();
		}
	}
	return TWDR;
}


void writeRegister(uint8_t address, uint8_t reg, uint8_t data) {
	twiStart();
	// send start condition
	twiWriteByte(address<<1,TW_MT_SLA_ACK);
	twiWriteByte(reg, TW_MT_SLA_ACK);
	twiWriteByte(data, TW_MT_SLA_ACK);
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	//send stop
	_delay_ms(1);
}

uint8_t readRegister(uint8_t address, uint8_t reg) {
	uint8_t data;
	twiStart();
	twiWriteByte(address<<1,TW_MT_SLA_ACK);
	twiWriteByte(reg, TW_MT_SLA_ACK);
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// send stop
	_delay_ms(1);
	twiStart();
	twiWriteByte(address<<1|1, TW_MT_SLA_ACK);
	data = twiRead(1);
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	// send stop
	_delay_ms(1);
	return data;
}