#include "header.h"

void sound(char* mes)
{
	int dis = atoi(buffer);

	if (strcmp(mes, "bu") == 0)
		digitalWrite(BUZZER, 1);
	else
		digitalWrite(BUZZER, 0);
}