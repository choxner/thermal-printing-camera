#pragma once

#include <stdint.h>

enum RESOLUTION{VGA, QVGA, QQVGA};
enum COLORSPACE{YUV422, RBG565, BAYER_RGB};

struct registerValueList {
	uint8_t registerNumber;
	uint8_t value;
};

void setColorSpace(enum COLORSPACE color);
void setResolution(enum RESOLUTION resolution);
void camInit(void);

#define OV7675_READ_ADDRESS		0x42
#define OV7675_WRITE_ADDRESS	0x43


#define	REG_BLUE	0x01	// blue channel gain
#define	REG_RED		0x02	// red channel gain
#define	REG_VREF	0x03	// vertical frame control
#define	REG_COM1	0x04	/*	bit[7]		debug mode
								bit[6]		CCIR656 format
								bit[5:2]	debug mode
								bit[1:0]	2 LSBs	*/
#define	REG_BAVE	0x05	// U/B avg level
#define	REG_BGAVE	0x06	// Y/Gb avg level
#define	REG_AECHH	0x07	/*	bit[7:6]	not used
								bit[5:0] 	AEC[15:10]	*/
#define	REG_RAVE	0x08	// V/R avg level
#define	REG_COM2	0x09	/*	bit[7:5]	debug mode
								bit[4]		soft sleep mode
								bit[3:2]	debug mode
								bit[1:0]	output drive capability (1x, 2x, 3x, 4x)	*/
#define	REG_PID		0x0a	// product id number
#define	REG_VER 	0x0b	// product id number
#define	REG_COM3	0x0c	/*	bit[7]		debug mode
								bit[6]		output data MSB and LSB swap
								bit[5]		tri state option for output clock at power down
								bit[4]		tri state option for output data at power down
								bit[3:0]	debug mode	*/
#define	REG_COM4	0x0d	/*	bit[7:6]	debug mode
								bit[5:4]	window size (must be same as REG_COM17[7:6])
								bit[3:0]	debug mode	*/
#define	REG_COM6	0x0f	/*	bit[7]		output of black line option
								bit[6:2]	debug mode
								bit[1]		reset all timing when format changes
								bit[0]		debug REG_DEBUG_MODE*/
#define	REG_AECH 	0x10 	// exposure value
#define	REG_CLKRC	0x11	/*	internal clock
								bit[7]		debug
								bit[6] 		use external clock
								bit[5:0]	internal clock pre scalar	*/
#define	REG_COM7 	0x12	/*	bit[7]		SCCB register reset
								bit[6:5]	debug mode
								bit[4]		QVGA selection
								bit[3]		debug mode
								bit[2]		RGB selection
								bit[1]		color bar
								bit[0]		raw RGB 	*/
#define	REG_COM8	0x13	/*	bit[7]	enable fast AGC/AEC
								bit[6]	AEC step size
								bit[5]	banding filter
								bit[4]	debug mode
								bit[3]	pixel level exposure
								bit[2]	AGC enable
								bit[1]	AWB enable
								bit[0]	AEC enable	*/
#define	REG_COM9	0x14	/*	bit[7]		debug mode
								bit[6:4]	gain ceiling, minimum AGC value
								bit[3:1]	debug mode
								bit[0]		freeze AGC/AEC 	*/
#define	REG_COM10	0x15	/*	bit[7]	debug mode
								bit[6]	HREF changes to HSYNC
								bit[5]	PCLK output option
								bit[4]	PCLK reverse
								bit[3]	HREF reverse
								bit[2]	VSYNC option
								bit[1]	VSYNC negative
								bit[0]	HSYNC negative 	*/
#define	REG_HSTART	0x17	// horizontal frame start 8 MSBs
#define	REG_HSTOP	0x18	// horizontal frame end 8 MSBs
#define	REG_VSTART	0x19	// vertical frame start 8 MSBs
#define	REG_VSTOP	0x1a	// vertical frame end 8 MSBs
#define	REG_PSHFT	0x1b	// data format
#define	REG_MIDH	0x1c	// manufacturer id high
#define	REG_MIDL	0x1d	// manufacturer id low
#define	REG_MVFP	0x1e	/*	mirror vertical flip
								bit[7:6]	debug mode
								bit[5]		mirror enable
								bit[4]		vertical flip enable
								bit[3:0]	debug mode 	*/
#define	REG_AEW		0x24	// AEG/AEC stable operating region upper limit
#define	REG_AEB		0x25	// AEG/AEC stable operating region lower limit
#define	REG_VPT 	0x26	/*	AEG/AEC fast mode operating region
								bit[7:4]	high nibble of upper limit
								bit[3:0]	high nibble of lower limit	*/
#define	REG_EXHCH 	0x2a	/*	dummy pixel insert
								bit[7:4]	pixel insert in horizontal direction
								bit[3:2]	HSYNC falling edge delay
								bit[1:0]	HSYNC rising edge delay	*/
#define	REG_EXHCL	0x2b	// bit[7:0]	dummy pixel insert in horizontal direction
#define	REG_ADVFL	0x2d	// LSBs of insert dummy lines in vertical direction
#define	REG_ADVFH	0x2e	// MSBs of insert dummy lines in vertical direction
#define	REG_YAVE	0x2f	// Y/G channel avg value
#define	REG_HSYST	0x30 	// HSYNC rising edge delay 8 LSBs
#define	REG_HSYEN	0x31 	// HSYNC falling edge delay
#define	REG_HREF	0x32	/*	href control
								bit[7:6]	HREF edge offset to data output
								bit[5:3]	HREF end 3 LSBs
								bit[2:0]	HREF start 3 LSBs	*/
#define	REG_TSLB	0x3a	/*	line buffer test option
								bit[7:6]	debug mode
								bit[5]		negative image enable
								bit[4]		UV output value
								bit[3]		output sequence
								bit[2:1]	debug mode
								bit[0]		auto output window 	*/
#define	REG_COM11	0x3b	/*	bit[7]		night mode
								bit[6:5]	RAF[1:0]
								bit[4]		debug mode
								bit[3]		banding filter value select
								bit[2] 		debug mode
								bit[1]		exposure timing
								bit[0]		debug mode 	*/
#define	REG_COM12 	0x3c	/* 	bit[7]		HREF option
								bit[6:0]	debug mode 	*/
#define	REG_COM13 	0x3d	/*	bit[7] 		gamma denable
								bit[6]		UV saturation level
								bit[5:1]	reserved
								bit[0]		UV swap	*/
#define	REG_COM14	0x3e	/*	bit[7:5]	debug mode
								bit[4]		DCW scaling and PCLK enable
								bit[3]		debug mode
								bit[2:0]	PCLK divider 	*/
#define	REG_EDGE 	0x3f	// edge enhancement adjustment
#define	REG_COM15	0x40 	/*	bit[7:6]	data format
								bit[5:4]	RGB555/565 option
								bit[3:0]	debug mode 	*/
#define	REG_COM16	0x41 	/*	bit[7:6]	debug mode
								bit[5]		enable edge enhancement threshold
								bit[4]		de-noise threshold auto adjustment
								bit[3]		AWB gain enable
								bit[2]		reserved
								bit[1]		color matrix coefficient double option
								bit[0]		debug mode 	*/
#define	REG_COM17	0x42 	/*	bit[7:6]	AEC window
								bit[5:4]	debug mode
								bit[3]		DSP color bar enable
								bit[2:0]	debug mode 	*/
#define	REG_DNSTH	0x4c	// denoise strength
#define	REG_MTX1	0x4f	// matrix coefficient 1
#define	REG_MTX2	0x50	// matrix coefficient 2
#define	REG_MTX3	0x51	// matrix coefficient 3
#define	REG_MTX4	0x52	// matrix coefficient 4
#define	REG_MTX5	0x53	// matrix coefficient 5
#define	REG_MTX6	0x54	// matrix coefficient 16
#define	REG_BRIGHT	0x55	// brightness control
#define	REG_CONTRAS	0x56	// contrast control
#define	REG_CONTRAS_CENTER	0x57	// contrast center
#define	REG_MTXS	0x58	/*	bit[7]	auto contrast center enable
								bit[6]	debug mode
								bit[5] sign bit for MTX6
								bit[4] sign bit for MTX5
								bit[3] sign bit for MTX4
								bit[2] sign bit for MTX3
								bit[1] sign bit for MTX2
								bit[0] sign bit for MTX1 	*/
#define	REG_LCC1	0x62 	/*	lens correction option 1
								bit[7]		sign bit for x coordinate of lens correction center
								bit[6:0]	x coordinate of lens correction center 	*/
#define	REG_LCC2	0x63 	/*	lens correction option 2
								bit[7]		sign bit for y coordinate of lens correction center
								bit[6:0]	y coordinate of lens correction center 	*/
#define	REG_LCC3	0x64	// channel coefficient
#define	REG_LCC4	0x65 	// radius w/o compensation
#define	REG_LCC5	0x66	/*	lens correction option 6
								bit[7:3]	not used
								bit[2]		lens correction control select
								bit[1]		not used
								bit[0]		lens correction enable 	*/
#define	REG_MANU	0x67	// manual U value
#define	REG_MANV	0x68	// manual V value
#define	REG_GFIX	0x69	/*	fixed gain control
								bit[7:6]	fixed gain control for Gr
								bit[5:4]	fixed gain control for Gb
								bit[3:2]	fixed gain control for R
								bit[1:0]	fixed gain control for B 	*/
#define	REG_GREEN	0x6a	// AWB green channel gain setting
#define	REG_DBLV	0x6b	/*	bit[7:6]	PLL control
								bit[5:0]	debug mode 	*/
#define	REG_AWBCTR3	0x6c	// AWB control 3
#define	REG_AWBCTR2	0x6d	// AWB control 2
#define	REG_AWBCTR1	0x6e	// AWB control 1
#define	REG_SCALING_XSC	0x70 	/*	bit[7]		test pattern[0]
									bit[6:0]	not used 	*/
#define	REG_SCALING_YSC	0x71 	/*	bit[7]		test pattern[1]
									bit[6:0]	not used 	*/
#define	REG_74	0x74	/*	bit[7:5]	debug mode
							bit[4]		digital gain manual control
							bit[3:2]	debug mode
							bit[1:0]	digital gain manual control 	*/
#define	REG_75	0x75 	/*	bit[7:5]	not used
							bit[4:0]	edge enhancement lower limit	*/
#define	REG_76	0x76 	/*	bit[7]		black pixel correction enable
							bit[6]		white pixel correction enable
							bit[5]		not used
							bit[4:0]	edge enhancement higher limit 	*/
#define	REG_77	0x77	// bit[7:0] de noise offset
#define	REG_SLOP 	0x7a	// gamma curve highest segment slope
#define	REG_GAM1 	0x7b	// gamma curve segment 1 end point
#define	REG_GAM2 	0x7c	// gamma curve segment 2 end point
#define	REG_GAM3 	0x7d	// gamma curve segment 3 end point
#define	REG_GAM4 	0x7e	// gamma curve segment 4 end point
#define	REG_GAM5 	0x7f	// gamma curve segment 5 end point
#define	REG_GAM6 	0x80	// gamma curve segment 6 end point
#define	REG_GAM7 	0x81	// gamma curve segment 7 end point
#define	REG_GAM8 	0x82	// gamma curve segment 8 end point
#define	REG_GAM9 	0x83	// gamma curve segment 9 end point
#define	REG_GAM10	0x84	// gamma curve segment 10 end point
#define	REG_GAM11 	0x85	// gamma curve segment 11 end point
#define	REG_GAM12 	0x86	// gamma curve segment 12 end point
#define	REG_GAM13 	0x87	// gamma curve segment 13 end point
#define	REG_GAM14 	0x88	// gamma curve segment 14 end point
#define	REG_GAM15 	0x89	// gamma curve segment 15 end point
#define	REG_444	0x8c	/*	bit[7:2]	not used
							bit[1]		RGB444 enable
							bit[0]		RGB44 word format 	*/
#define	REG_DM_LNH	0x92	// dummy line 8 LSBs
#define	REG_LCC6	0x93	// dummy line 8 MSBs
#define	REG_LCC7	0x94	// lens correction option 6
#define	REG_BD50ST	0x9d	// 50Hz banding filter value
#define	REG_BD60ST	0x9e	// 60Hz banding filter value
#define	REG_NT_CTRL	0xa4	/*	bit[7:4]	not used
								bit[3]		auto frame adjustment control
								bit[2]		not used
								bit[1:0]	auto frame adjustment switch point 	*/
#define	REG_BD50MAX	0xa5 	// 50Hz banding step limit
#define	REG_BD60MAX	0xab 	// 60Hz banding step limit
#define	REG_SATCTR	0xc9	/*	saturation control
								bit[7:4]	UV saturation control min
								bit[3:0]	saturation control result 	*/
#define	REG_CA 	0xca	/*	bit[7:6]	dummy pixel insert in horizontal direction
							bit[5:0]	debug mode 	*/
#define	REG_REFCF 	0xcf	/* 	bit[7:4]	debug mode
								bit[3]		RAF[2]
								bit[2:0]	debug mode 	*/
#define	REG_RADCO	0xd4	/*	ADC control
								bit[7:3]	debug mode
								bit[2:0]	ADC referenced adjustment 	*/
#define	REG_RPWC2	0xdc	/*	bit[7:4]	debug mode
								bit[3]		regulator control 	*/
#define	REG_E1	0xe1 	/*	bit[7:4]	debug mode
								bit[3:2]	60 Hz banding value 2 MSBs
								bit[1:0]	50 Hz banding value 2 MSBs 	*/
#define	REG_RDSP0	0xe8 	/*	bit[7:1]	debug mode
								bit[0]		LCD gain adjustment enable 	*/
#define	REG_RDSP2 	0xea	/*	bit[7:6] 	debug mode
								bit[5:4] 	LCD gain of red channel
								bit[3:0]	fraction LCD gain of red  	*/
#define	REG_RDSP3 	0xeb	/*	bit[7:6] 	debug mode
								bit[5:4] 	LCD gain of green channel
								bit[3:0]	fraction LCD gain of greem  	*/
#define	REG_RDSP4 	0xec	/*	bit[7:6] 	debug mode
								bit[5:4] 	LCD gain of blue channel
								bit[3:0]	fraction LCD gain of blue  	*/