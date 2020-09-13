#pragma once

#include <stdint.h>

struct registerValueList {
	uint8_t registerNumber;
	uint8_t value;
};

void chargeInit(void);

#define BQ24295_ADDRESS	0x6b

#define	CHARGE_REG00	0x00
#define CHARGE_REG01	0x01
#define CHARGE_REG02	0x02
#define CHARGE_REG03	0x03
#define CHARGE_REG04	0x04
#define CHARGE_REG05	0x05
#define CHARGE_REG06	0x06
#define CHARGE_REG07	0x07