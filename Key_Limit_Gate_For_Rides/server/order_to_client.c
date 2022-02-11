#include "header.h"

//���ɾ� ���� �Լ�
int order(char *msg, char *ip, int serial, int come)
{
	int dis = atoi(msg);
	if (dis <= 60)
	{
		log_file2(ip);
		strcpy(msg, "green");
		pthread_mutex_lock(&mutx);
		boolean = 1;
		pthread_mutex_unlock(&mutx);
		come = 0;
		gate[serial] = 0;
	}
	else if (dis > 60 && dis <= 170 && boolean == 1)
	{
		boolean = 0;
		strcpy(msg, "red");
	}
	else if (dis > 60 && dis <= 170)
	{
		strcpy(msg, "red");
	}
	else
	{
		strcpy(msg, "red");
		come++;
		if (come == 4)
		{
			gate[serial] = 1;
		}
	}
	return come;
}

//��� ���� ����Ʈ Ȯ��
void order2(char *msg, int serial)
{
	int a[5], cnt = 0;
	char temp[10];
	strcpy(msg, "\0");
	for (int i = 0; i < clnt_cnt; i++)
	{
		if (gate[i] == 1)
		{
			a[cnt] = i;
			cnt++;
		}
	}
	if (cnt != 0)
	{
		strcat(msg, "please move to ");
		for (int i = 0; i < cnt; i++)
		{
			sprintf(temp, "%d", a[i] + 1);
			strcat(msg, temp);
			strcat(msg, " gate ");
		}
	}
	else
	{
		strcat(msg, "All gate is full. Please wait.");
	}
}