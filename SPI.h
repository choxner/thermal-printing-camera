#ifndef	SPI_H_
#define SPI_H_

struct spiDevice {
	char startingBit,	// 'm' or 'l'
	int transferSpeed,
	int mode,
}

void spiConfig(void);

#endif /* SPI_H_ */