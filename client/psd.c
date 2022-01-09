#include "header.h"

int psd_sensor()
{
	int adcValue = 0, i;
	unsigned char buf[3];
	char adChannel = ADC_CH3;
	int psdValue = 0;

	// psd
	pinMode(ADC_CS, OUTPUT);

	if (wiringPiSPISetup(SPI_CH, SPI_SPEED) == -1)
	{
		printf("wiringPi SPI Setup falied!\n");
		exit(0);
	}
	// PSD Sensor
	buf[0] = 0x06 | ((adChannel & 0x07) >> 2);
	buf[1] = ((adChannel & 0x07) << 6);
	buf[2] = 0x00;

	digitalWrite(ADC_CS, 0);
	wiringPiSPIDataRW(SPI_CH, buf, 3);

	buf[1] = 0x0F & buf[1];
	adcValue = (buf[1] << 8) | buf[2];

	digitalWrite(ADC_CS, 1);
	psdValue = 10000 / (adcValue * 434 * 5 / 1023 - 46);

	return psdValue;
}