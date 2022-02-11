#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <wiringPi.h>
#include <time.h>

#define BUF_SIZE 1024

/*
** psd
*/
#define ADC_CS 8
#define ADC_CH3 3
#define SPI_CH 0
#define SPI_SPEED 500000

/*
** distance sencor
*/
#define trigPin 28
#define echoPin 29

/*
** DC MOTOR
*/
#define DC_INA 26
#define DC_INB 23
#define DC_ENCA 10
#define DC_ENCB 11

/*
** LED Sensor
*/
#define RED 7
#define GREEN 21

/*
** DC Motor
*/
static unsigned long int EN_count = 0;
static char clockwise = 0;
static char message[BUF_SIZE];
static int boolean = 0;
static int gate_open = 0;
static int info = 0;

/*
** psd
*/
static int distance = 0, i;
static long startTime, travelTime;

/*
** DC Motor Function
*/
int psd_sensor();
void ENCA_interrupt();
void ENCB_interrupt();
void Motor_CW();
void Motor_CCW();
void motor();
void error_handling(char *message);
void *send_msg(void *arg);
void *recv_msg(void *arg);
void *thread_sensor(void *arg);
void light(char* mes);
pthread_mutex_t mutx;

#endif