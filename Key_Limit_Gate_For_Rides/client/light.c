#include "header.h"

void light(char *mes)
{
	if (strcmp(mes, "red") == 0)
	{
		digitalWrite(GREEN, 0);
		digitalWrite(RED, 1);
	}
	else if (strcmp(mes, "green") == 0)
	{
		digitalWrite(RED, 0);
		digitalWrite(GREEN, 1);
	}
}
