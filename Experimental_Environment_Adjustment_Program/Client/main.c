#include "header.h"

int main(int argc, char *argv[])
{
	float temp;
	int x;
	struct sockaddr_in p;
	struct hostent *host;
	char message[100] = "";
	char buf[100];
	char buffer[BUFSIZ];
	pid_t pid;

	if ((x = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("client: socket");
		return 1;
	}
	host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		printf("Host not found !!: %s\n\r", argv[1]);
		return 1;
	}
	bzero((char *)&p, sizeof(p));
	p.sin_family = AF_INET;
	memcpy((char *)&p.sin_addr, host->h_addr, host->h_length);
	p.sin_port = htons(atoi(argv[2]));

	inet_ntop(AF_INET, &p.sin_addr, buf, sizeof(buf));
	printf("Trying %s ...\n", buf);
	if (connect(x, (struct sockaddr *)&p, sizeof(p)) == -1)
	{
		perror("client: connect");
		return 1;
	}
	printf("Connected %s...\n", argv[1]);

	if (wiringPiSetup() == -1)
	{
		return 1;
	}

	////-------- GPIO ------------
	//step
	pinMode(STEP_OUT1A, OUTPUT);
	pinMode(STEP_OUT1B, OUTPUT);
	pinMode(STEP_OUT2A, OUTPUT);
	pinMode(STEP_OUT2B, OUTPUT);
	//dc
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

	while (1)
	{
		pid = fork();

		if (pid == -1)
		{
			continue;
		}

		else if (pid == 0)
		{
			while (1)
			{
				int str_len = read(x, message, sizeof(message));
				if (str_len == -1)
				{
					perror("parent client: read");
					break;
				}
				if (str_len == 0)
					break;
				puts(message);
				moter(message);
				strcpy(message, "\0");
			}
			close(x);
			return 0;
		}
		else
		{
			if (wiringPiSetup() == -1)
			{
				return 1;
			}

			while (1)
			{
				temp = dht11_read_val();

				sprintf(message, "%f", temp);

				if (write(x, message, strlen(message) + 1) == -1)
				{
					perror("client: write");
					break;
				}
				strcpy(message, "\0");
				sleep(10);
			}
		}
	}
	close(x);
	return 0;
}