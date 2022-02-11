#include "header.h"

double speed(int dis[])
{
	double tmp = 0;
	double sp;
	for (int i = 0; i < 19; i++)
	{
		tmp = tmp + (dis[i] - dis[i + 1]);
	}
	sp = tmp / 20.;
	return sp;
}
