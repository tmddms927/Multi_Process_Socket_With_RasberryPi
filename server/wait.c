#include "header.h"

//�̰� �����ؾߵ�
void wait(char *msg)
{
	int log_fi, len, w_time = 0;
	char buffer[100];

	log_fi = open("log_file.txt", O_RDONLY, 0644);
	//len = read(log_fi, buf, BUF_SIZE);
	//len = write(1, buf, len);
	//write(log_fi, log_ip, strlen(log_ip));
	close(log_fi);
	pthread_mutex_lock(&mutx);
	boolean = 0;
	pthread_mutex_unlock(&mutx);
	//strcpy(msg, "��� �ð� : %d��", w_time);
	strcat(msg, "waiting time : ");
}