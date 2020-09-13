#pragma once

#include <stdint.h>	// bit and byte info

void writeRegister(uint8_t reg, uint8_t data);
uint8_t readRegister(uint8_t reg);