#include "header.h"

void order(char *buffer)
{
	int dis = atoi(buffer);

	if (dis > 20)
		strcpy(buffer, "red");
	else if (dis == 20)
		strcpy(buffer, "blue");
	else
		strcpy(buffer, "green");
}

void order2(char *buffer, int bu1, int bu)
{
	// int dis = atoi(buffer);

	if ((bu - bu1) >= 3)
		strcpy(buffer, "bu");
	else
		strcpy(buffer, "nn");
}

void red_order(char *buffer, double sp)
{
	int time = 0;
	double dis = atof(buffer);
	time = (dis - 100) / sp;
	sprintf(buffer, "%f", sp);
	puts(buffer);
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}
