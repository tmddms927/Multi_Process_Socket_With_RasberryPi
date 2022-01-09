#include "header.h"

void log_file(char *log_ip)
{
	int log_fi;
	struct tm *t;
	time_t timer;
	char *buf;
	char *buf2 = "client connect\n";
	buf = (char *)malloc(50);

	//���ӽð� Ȯ��
	timer = time(NULL);
	t = localtime(&timer);

	//�α����Ͽ� ���� ip�� �ð� ����
	strcat(buf, log_ip);
	strcat(buf, timeToString(t));
	strcat(buf, buf2);
	log_fi = open("log_file.txt", O_WRONLY | O_APPEND, 0664);
	write(log_fi, buf, strlen(buf));
	close(log_fi);
	free(buf);
}

void log_file2(char *ip)
{
	int log_fi;
	struct tm *t;
	time_t timer;
	char *buf;
	char *buf2 = "come in to ride\n";
	buf = (char *)malloc(50);

	//���ӽð� Ȯ��
	timer = time(NULL);
	t = localtime(&timer);

	//�α����Ͽ� ���� ip�� �ð� ����
	strcat(buf, ip);
	strcat(buf, timeToString(t));
	strcat(buf, buf2);
	log_fi = open("log_file.txt", O_WRONLY | O_APPEND, 0664);
	write(log_fi, buf, strlen(buf));
	close(log_fi);
	free(buf);
}

char* timeToString(struct tm *t)
{
	static char s[30];
	sprintf(s, "     %04d-%02d-%02d %02d:%02d:%02d\t",
		t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
		t->tm_hour, t->tm_min, t->tm_sec
	);
	return s;
}