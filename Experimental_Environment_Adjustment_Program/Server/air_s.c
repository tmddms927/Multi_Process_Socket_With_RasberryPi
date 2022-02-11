#include "header.h"

void getAve(double temp[])
{
	double tmp = (temp[0] + temp[1]) / 2.;
	temp[2] = tmp;
}

void order(double temp[], char *buffer, int i)
{
	strcpy(buffer, "\0");
	if (temp[i] > temp[2])
		strcpy(buffer, "hot");
	else if (temp[i] < temp[2])
		strcpy(buffer, "cold");
	else if (temp[i] == temp[2])
		strcpy(buffer, "average");

}
