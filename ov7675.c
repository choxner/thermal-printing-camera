#include <stdint.h>	// bit and byte info
#include <avr/io.h>	// control pins
#include <util/twi.h>	// use i2c protocol
#include <util/delay.h>	// enable delays
#include <avr/pgmspace.h>	// needed for PROGMEM
#include "ov7675.h"	// use .h counterpart
#include "i2c.c" // use i2c methods

static const struct registerValueList vga[] PROGMEM = {
	{REG_HREF, 0x80},		
	{REG_HSTART, 0x08},	
	{REG_HSTOP, 0x4d},
	{REG_VSTART, 0x0c},
	{REG_VSTOP, 0x6c},
	{REG_VREF, 0x00},
	{0xff, 0xff},			// end marker
}

// add color type registerValueList

static const struct registerValueList defaults[] PROGMEM = {
	{REG_BLUE,0x00},
	{REG_RED,0x80},
	{REG_VREF,0x80},
	{REG_COM1,0x00},
	{REG_BAVE,0x00},
	{REG_BGAVE,0x00},
	{REG_AECHH,0x00},
	{REG_RAVE,0x00},
	{REG_COM2,0x01},
	{REG_PID,0x76},
	{REG_VER,0x73},
	{REG_COM3,0x00},
	{REG_COM4,0x00},
	{REG_COM6,0x43},
	{REG_AECH,0x40},
	{REG_CLKRC,0x80},
	{REG_COM7,0x00},
	{REG_COM8,0x8f},
	{REG_COM9,0x4a},
	{REG_COM10,0x00},
	{REG_HSTART,0x11},
	{REG_HSTOP,0x61},
	{REG_VSTART,0x03},
	{REG_VSTOP,0x7b},
	{REG_PSHFT,0x00},
	{REG_MIDH,0x7f},
	{REG_MIDL,0xa2},
	{REG_MVFP,0x01},
	{REG_AEW,0x62},
	{REG_AEB,0x58},
	{REG_VPT,0x93},
	{REG_EXHCH,0x00},
	{REG_EXHCL,0x00},
	{REG_ADVFL,0x00},
	{REG_ADVFH,0x00},
	{REG_YAVE,0x00},
	{REG_HSYST,0x08},
	{REG_HSYEN,0x30},
	{REG_HREF,0x80},
	{REG_TSLB,0x0d},
	{REG_COM11,0x00},
	{REG_COM12,0x68},
	{REG_COM13,0x88},
	{REG_COM14,0x00},
	{REG_EDGE,0x00},
	{REG_COM15,0xc0},
	{REG_COM16,0x38},
	{REG_COM17,0x00},
	{REG_DNSTH,0x00},
	{REG_MTX1,0x96},
	{REG_MTX2,0x9b},
	{REG_MTX3,0x05},
	{REG_MTX4,0x1a},
	{REG_MTX5,0x7f},
	{REG_MTX6,0x54},
	{REG_BRIGHT,0x00},
	{REG_CONTRAS,0x40},
	{REG_CONTRAS_CENTER,0x80},
	{REG_MTXS,0x1a},
	{REG_LCC1,0x00},
	{REG_LCC2,0x00},
	{REG_LCC3,0x50},
	{REG_LCC4,0x30},
	{REG_LCC5,0x00},
	{REG_MANU,0x80},
	{REG_MANV,0x80},
	{REG_GFIX,0x00},
	{REG_GREEN,0x40},
	{REG_DBLV,0x0a},
	{REG_AWBCTR3,0x0a},
	{REG_AWBCTR2,0x65},
	{REG_AWBCTR1,0x11},
	{REG_AWBCTR0,0x9f},
	{REG_SCALING_XSC,0x3a},
	{REG_SCALING_YSC,0x35},
	{REG_74,0x00},
	{REG_75,0x0f},
	{REG_76,0x01},
	{REG_77,0x10},
	{REG_SLOP,0x28},
	{REG_GAM1,0x04},
	{REG_GAM2,0x09},
	{REG_GAM3,0x16},
	{REG_GAM4,0x30},
	{REG_GAM5,0x3e},
	{REG_GAM6,0x4b},
	{REG_GAM7,0x59},
	{REG_GAM8,0x67},
	{REG_GAM9,0x72},
	{REG_GAM10,0x7c},
	{REG_GAM11,0x8e},
	{REG_GAM12,0x9e},
	{REG_GAM13,0xb6},
	{REG_GAM14,0xcc},
	{REG_GAM15,0xe2},
	{REG_444,0x00},
	{REG_DM_LNH,0x00},
	{REG_LCC6,0x50},
	{REG_LCC7,0x50},
	{REG_BD50ST,0x7f},,
	{REG_BD60ST,0xc0},
	{REG_NT_CTRL,0x00},
	{REG_BD50MAX,0x0f},
	{REG_BD60MAX,0x0f},
	{REG_CA,0x00},
	{REG_REFCF,0x84},
	{REG_RADCO,0x84},
	{REG_RPWC2,0x35},
	{REG_E1,0x40},
	{REG_RDSP0,0x15},
	{REG_RDSP2,0x10},
	{REG_RDSP3,0x10},
	{REG_RDSP4,0x10},
	{0xff,0xff},			// end marker
}

static void writeSensorRegs8_8(const struct registerValueList regval_list[]) {
	const struct regval_list * next = reglist;
	for(;;) {
		uint8_t reg_addr = pgm_read_byte(&next -> reg_num);
		uint8_t reg_val = pgm_read_byte(&next -> value);
		if ((reg_addr == 255) && (reg_val == 255))
			break;
		writeRegister(reg_addr, reg_val);
		next++;
	}
}

void camInit(void) {
	writeRegister(OV7675_ADDRESS, 0x12, 0x80);
	_delay_ms(100);
	writeSensorRegs8_8(defaults);
	_delay_ms(100);
	// set resolution
	// set window width
	// set color space
	writeRegister(REG_COM10, 32);
	//PCLK does not toggle on HBLANK
}