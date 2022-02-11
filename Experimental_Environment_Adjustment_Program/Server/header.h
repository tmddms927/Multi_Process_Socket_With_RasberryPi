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

#define bufsiz 100

void setMessage(void *buffer, int dis);
void read_childproc(int sig);
void error_handling(char *message);
void getAve(double temp[]);
void order(double temp[], char *buffer, int i);

#endif