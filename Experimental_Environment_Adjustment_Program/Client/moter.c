#include "header.h"

void moter(char* mes)
{
	int i;

	if (strcmp(mes, "") == 0 || strcmp(mes, "average") == 0)
	{
		digitalWrite(DC_INA, 0);
		digitalWrite(DC_INB, 0);
		digitalWrite(STEP_OUT2B, 0);
		digitalWrite(STEP_OUT2A, 0);
		digitalWrite(STEP_OUT1B, 0);
		digitalWrite(STEP_OUT1A, 0);
	}
	else if (strcmp(mes, "hot") == 0)
	{
		Motor_CW();
	}
	else if (strcmp(mes, "cold") == 0)
	{
		//�ð����
		for (i = 0; i < 1000; i++)
		{
			digitalWrite(STEP_OUT2B, 1);
			digitalWrite(STEP_OUT2A, 0);
			digitalWrite(STEP_OUT1B, 0);
			digitalWrite(STEP_OUT1A, 0);
			usleep(3000);

			digitalWrite(STEP_OUT2B, 0);
			digitalWrite(STEP_OUT2A, 1);
			digitalWrite(STEP_OUT1B, 0);
			digitalWrite(STEP_OUT1A, 0);
			usleep(3000);

			digitalWrite(STEP_OUT2B, 0);
			digitalWrite(STEP_OUT2A, 0);
			digitalWrite(STEP_OUT1B, 1);
			digitalWrite(STEP_OUT1A, 0);
			usleep(3000);

			digitalWrite(STEP_OUT2B, 0);
			digitalWrite(STEP_OUT2A, 0);
			digitalWrite(STEP_OUT1B, 0);
			digitalWrite(STEP_OUT1A, 1);
			usleep(3000);
		}
	}
}