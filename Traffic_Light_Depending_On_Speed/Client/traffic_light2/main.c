#include "header.h"

int main(int argc, char *argv[])
{
	//rasberry setting
	int distance = 80;
	long startTime, travelTime;

	int x, i, time;
	struct sockaddr_in p;
	struct hostent *host;   // DNS processing ---
	char message[100] = "";
	char buf[100];        // Dotted decimal
	char buffer[BUFSIZ];
	pid_t pid;
	int fd1[2];

	if ((x = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("client: socket");
		return 1;
	}
	//--- DNS ---
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

	if (pipe(fd1) < 0)
		error_handling("Pipe() error!!");

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

	//-------- GPIO ------------
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(Red, OUTPUT);
	pinMode(Green, OUTPUT);
	pinMode(Blue, OUTPUT);
	digitalWrite(Red, 1);
	digitalWrite(Green, 0);
	digitalWrite(Blue, 0);

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
				time = atoi(message);
				read(fd1[0], message, sizeof(message));
				//puts(message);
				distance = atoi(message);
				time = (time - 20) / time;
				sleep(time);
				digitalWrite(Red, 0);
				digitalWrite(Blue, 1);
				sleep(1);
				digitalWrite(Blue, 0);
				digitalWrite(Green, 1);
				strcpy(message, "\0");
				time = 20 / time;
				sleep(time);
				digitalWrite(Green, 0);
				digitalWrite(Red, 1);
			}
			close(x);
			return 0;
		}

		else
		{
			while (1)
			{
				digitalWrite(trigPin, LOW);
				usleep(2);
				digitalWrite(trigPin, HIGH);
				usleep(20);
				digitalWrite(trigPin, LOW);

				while (digitalRead(echoPin) == LOW);
				startTime = micros();
				while (digitalRead(echoPin) == HIGH);
				travelTime = micros() - startTime;

				distance = travelTime * 17 / 1000;
				//printf("Distance: %d cm\n", distance);

				sprintf(message, "%d", distance);
				write(fd1[1], message, strlen(message));

				if (write(x, message, strlen(message) + 1) == -1)
				{
					perror("client: write");
					break;
				}
			}
		}
	}
	close(x);
	return 0;
}