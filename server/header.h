#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>

#define BUF_SIZE 100
#define MAX_CLNT 5

static int clnt_cnt = 0;
static int clnt_socks[MAX_CLNT];
static pthread_mutex_t mutx;
static int boolean = 0;
static char *log_ip;
static int gate[5];

/*
** function
*/
void * handle_clnt(void * arg);
void error_handling(char * msg);
int order(char *msg, char *ip, int serial, int come);
void log_file(char *log_ip);
char* timeToString(struct tm *t);
void wait(char *msg);
void log_file2(char *ip);
void order2(char *msg, int serial);
