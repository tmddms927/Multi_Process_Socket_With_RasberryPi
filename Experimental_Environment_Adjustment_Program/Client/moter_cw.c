#include "header.h"

void Motor_CW()
{
	int i;
	for (i = 0; i < 7; i++) {
		digitalWrite(DC_INA, 0);
		digitalWrite(DC_INB, 1);
		sleep(1);
		//printf("Motor Encode -> %d\n", EN_count);

		//if (clockwise == 1) printf("Clockwise\n");
		//else printf("CountClockwise\n");
	}
	digitalWrite(DC_INA, 0);
	digitalWrite(DC_INB, 0);
	EN_count = 0;
}