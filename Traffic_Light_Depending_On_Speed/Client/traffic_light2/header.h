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
#define Red 7  // BCM 25, GND-GND
#define Green 21
#define Blue 22
#define trigPin 28
#define echoPin 29

void light(char* mes);
void error_handling(char *message);

#endif