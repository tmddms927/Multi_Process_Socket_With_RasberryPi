#include "header.h"

void ENCA_interrupt()
{
	char ENCB;
	if (digitalRead(DC_ENCA) == 1)
	{
		ENCB = digitalRead(DC_ENCB);
		if (ENCB == 1)
			clockwise = 1;
		else
			clockwise = 0;
	}
	EN_count++;
}

void ENCB_interrupt()
{
	EN_count++;
}