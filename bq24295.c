#include <avr/pgmspace.h>
#include <stdint.h>	// bit and byte info
#include "bq24295.h"	// use .h counterpart
#include "i2c.c" // use i2c methods

static const struct registerValueList chargeDefaults[] PROGMEM = {
	{CHARGE_REG00,0b00100101},	/*	[7] 	HIZ off
									[6,3]	set max voltage at 4.2V
									[2,1]	1.5A max current	*/
	{CHARGE_REG01,0b00111011},	/*	[7]		keep register
									[6]		keep timer
									[5]		OTG enable
									[4]		charge enable
									[3,1]	minimum sys voltage	
									[0]		1 (reserved)	*/
	{CHARGE_REG02,0b01101000},	/*	[7,2]	fast charge limit 1.66A
									[1]		temperature threshold enabled
									[0]		charge speed high	*/
	{CHARGE_REG03,0b00010001},	/*	[7,4]	pre-charge default current
									[3,0]	termination default current	*/
	{CHARGE_REG04,0b10110010},	/*	[7,2]	charge limit 4.2V
									[1]		low battery 3V
									[0]		recharge threshold .1V	*/
	{CHARGE_REG05,0b10011100},	/*	[7]		enable termination
									[6]		0 (reserved)
									[5,4]	40s watchdog timer
									[3]		enable safety timer
									[2,1]	12h safety timer
									[0]		0 (reserved)	*/
	{CHARGE_REG06,0b10010011},	/*	[7,4]	5.126V PMID
									[3,2]	enable temperature limit on boost
									[1,0]	temperature limit is 120C	*/
	{CHARGE_REG07,0b},
	{0xff,0xff},	// end marker
}


static void writeChargerRegs8_8(const struct registerValueList regval_list[]) {
	const struct regval_list * next = reglist;
	for(;;) {
		uint8_t reg_addr = pgm_read_byte(&next -> reg_num);
		uint8_t reg_val = pgm_read_byte(&next -> value);
		if ((reg_addr == 255) && (reg_val == 255))
			break;
		writeRegister(BQ24295_ADDRESS, reg_addr, reg_val);
		next++;
	}
}

void chargeInit(void) {
	writeChargerRegs8_8(defaults);
	_delay_ms(100);
}