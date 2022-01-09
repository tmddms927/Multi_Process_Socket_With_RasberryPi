#include "header.h"

void * handle_clnt(void * arg)
{
	int clnt_sock = *((int*)arg);
	int str_len = 0, i;
	char ip[30];
	char msg[BUF_SIZE];
	int serial = clnt_cnt - 1;
	strcpy(ip, log_ip);
	gate[serial] = 0;
	int come = 0;

	str_len = read(clnt_sock, msg, sizeof(msg));
	msg[str_len] = 0;
	while (str_len != 0)
	{
		puts(msg);
		come = order(msg, ip, serial, come);
		puts(msg);
		write(clnt_sock, msg, strlen(msg));
		strcpy(msg, "\0");
		if (boolean == 1)
		{
			order2(msg, serial);
			//write(clnt_sock, msg, strlen(msg));
			//wait(msg);
			write(clnt_sock, msg, strlen(msg));
			strcpy(msg, "\0");
			puts(msg);
		}
		str_len = read(clnt_sock, msg, sizeof(msg));
		msg[str_len] = 0;
	}
	close(clnt_sock);
	return NULL;
}