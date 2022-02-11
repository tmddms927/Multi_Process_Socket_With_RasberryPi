#include "header.h"

void light(char* mes)
{
	digitalWrite(Red, 0);
	digitalWrite(Blue, 0);
	digitalWrite(Green, 0);

	if(strcmp(mes, "red") == 0)
		digitalWrite(Red, 1);
	else if (strcmp(mes, "blue") == 0)
		digitalWrite(Blue, 1);
	else if (strcmp(mes, "green") == 0)
		digitalWrite(Green, 1);
}