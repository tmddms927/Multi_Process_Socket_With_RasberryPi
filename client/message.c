#include "header.h"

void *send_msg(void *arg)
{
	int sock = *((int *)arg);
	while (1)
	{
		if (boolean == 2)
		{
			write(sock, message, strlen(message));
			pthread_mutex_lock(&mutx);
			boolean = 1;
			pthread_mutex_unlock(&mutx);
		}
	}
	return NULL;
}

void *recv_msg(void *arg)
{
	int sock = *((int *)arg);
	int str_len;

	while (1)
	{
		if (boolean == 1)
		{
			str_len = read(sock, message, BUF_SIZE - 1);
			if (str_len == -1)
				return (void *)-1;
			message[str_len] = 0;
			light(message);
			moter(message);
			strcpy(message, "\0");
			if (gate_open == 1 && info == 1)
			{
				str_len = read(sock, message, BUF_SIZE - 1);
				message[str_len] = 0;
				puts(message);
				strcpy(message, "\0");
				info = 0;
			}
		}
	}
	return NULL;
}
