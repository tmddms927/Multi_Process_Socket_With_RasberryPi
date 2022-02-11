#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wiringPi.h>

#define MAX_TIME 100
#define DHT11PIN 25
//dc ����
#define DC_INA 26
#define DC_INB 23
#define DC_ENCA 10
#define DC_ENCB 11
//step ����
#define STEP_OUT1A 27
#define STEP_OUT1B 0
#define STEP_OUT2A 1
#define STEP_OUT2B 24

void moter(char* mes);
float dht11_read_val();
void ENCA_interrupt();
void ENCB_interrupt();
void Motor_CW();
void setMessage(void *buffer, int dis);
void read_childproc(int sig);
void error_handling(char *message);
void getAve(double temp[]);
void order(double temp[], char *buffer, int i);

static unsigned long int EN_count = 0;
static char clockwise = 0;

static int dht11_val[5] = { 0, 0, 0, 0, 0 };
static int dht11_temp[5] = { 0, 0, 0, 0, 0 };

#endif