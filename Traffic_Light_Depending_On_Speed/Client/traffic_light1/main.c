#include "header.h"

int main(int argc, char *argv[])
{
	//rasberry setting
	int distance;
	//long startTime, travelTime;

	int x, i;
	struct sockaddr_in p;
	struct hostent *host;   // DNS processing ---
	char message[100] = "";
	char buf[100];        // Dotted decimal
	char buffer[BUFSIZ];
	pid_t pid;

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
	pinMode(BUZZER, OUTPUT);

	digitalWrite(BUZZER, 0);

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
				light(message);
				strcpy(message, "\0");
				int str_len = read(x, message, sizeof(message));
				if (str_len == -1)
				{
					perror("parent client: read");
					break;
				}
				if (str_len == 0)
					break;
				puts(message);
				sound(message);
				strcpy(message, "\0");
			}
			close(x);
			return 0;
		}

		else
		{
			while(1)
			{
				digitalWrite(trigPin, LOW);
				usleep(2);
				digitalWrite(trigPin,HIGH);
				usleep(20);
				digitalWrite(trigPin,LOW);

				while (digitalRead(echoPin) == LOW);
				startTime = micros();
				while (digitalRead(echoPin) == HIGH);
				travelTime = micros()-startTime;

				distance = travelTime * 17 / 1000;
				//printf("Distance: %d cm\n", distance);

				sprintf(message, "%d", distance);

				if (write(x, message, strlen(message) + 1) == -1)
				{
					perror("client: write");
					break;
				}
				sleep(1);
				strcpy(message, "\0");
			}
		}
	}
	close(x);
	return 0;
}
