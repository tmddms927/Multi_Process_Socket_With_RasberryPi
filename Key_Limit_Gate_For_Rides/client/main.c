#include "header.h"

int main(int argc, char *argv[])
{
	int sock;
	int str_len;
	int clnt_sock;
	int serv_sock;
	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_addr;
	pthread_t snd_thread, rcv_thread, sensor_thread;
	socklen_t clnt_addr_size;
	void *thread_return;

	if (argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if (connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected...........");

	if (wiringPiSetup() == -1)
		return -1;

	//???œÆ? Œ?Œ
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	// DC Œ?Œ
	pinMode(DC_INA, OUTPUT);
	pinMode(DC_INB, OUTPUT);
	pinMode(DC_ENCA, OUTPUT);
	pinMode(DC_ENCB, OUTPUT);
	digitalWrite(DC_INA, 0);
	digitalWrite(DC_INB, 0);
	pullUpDnControl(DC_ENCA, PUD_UP);
	pullUpDnControl(DC_ENCB, PUD_UP);
	wiringPiISR(DC_ENCA, INT_EDGE_BOTH, &ENCA_interrupt);
	wiringPiISR(DC_ENCB, INT_EDGE_BOTH, &ENCB_interrupt);

	//º? Œ?Œ
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	digitalWrite(RED, 1);
	digitalWrite(GREEN, 0);

	pthread_create(&sensor_thread, NULL, thread_sensor, (void *)&sock);
	pthread_create(&snd_thread, NULL, send_msg, (void *)&sock);
	pthread_create(&rcv_thread, NULL, recv_msg, (void *)&sock);
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);
	pthread_join(sensor_thread, &thread_return);

	close(sock);
	return 0;
}
