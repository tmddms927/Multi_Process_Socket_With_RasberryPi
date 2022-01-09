#include "header.h"

void Motor_CW()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		digitalWrite(DC_INA, 0);
		digitalWrite(DC_INB, 1);
		sleep(1);
	}
	digitalWrite(DC_INA, 0);
	digitalWrite(DC_INB, 0);
	EN_count = 0;
}

void Motor_CCW()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		digitalWrite(DC_INB, 0);
		digitalWrite(DC_INA, 1);
		sleep(1);
	}
	digitalWrite(DC_INB, 0);
	digitalWrite(DC_INA, 0);
	EN_count = 0;
}

void moter(char *mes)
{
	int i;
	if (strcmp(mes, "") == 0 || strcmp(mes, "red") == 0 && gate_open == 0)
	{
		digitalWrite(DC_INA, 0);
		digitalWrite(DC_INB, 0);
	}
	else if (strcmp(mes, "green") == 0 && gate_open == 0)
	{
		Motor_CW();
		gate_open = 1;
		info = 1;
	}
	else if (gate_open == 1 && strcmp(mes, "red") == 0)
	{
		Motor_CCW();
		gate_open = 0;
	}
}