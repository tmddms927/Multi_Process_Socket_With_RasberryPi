#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFSIZ 100

void read_childproc(int sig);
void error_handling(char *message);
void red_order(char *buffer, double sp);
double speed(int dis[]);
void order(char *buffer);
void order2(char *buffer, int bu1, int bu);

#endif