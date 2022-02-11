#include "header.h"

int main(int argc, char *argv[])
{
	int x, y, state, i = 0;
	int distance;
	int clilen;
	struct sockaddr_in addr, cli_addr;
	struct sigaction act;
	char buf[100];
	char buffer[BUFSIZ];
	char message[10];
	int fd1[2], fd2[2];
	pid_t pid;
	int str_len = 0;
	int fork_num = 0;
	double sp = 0;
	int bu = 0, bu1 = 0;

	int dis[20];

	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	if ((x = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("server: socket");
		return 1;
	}
	memset(&addr, 0, sizeof(addr));

	if (pipe(fd1) < 0 || pipe(fd2) < 0)
		error_handling("Pipe() error!!");

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(atoi(argv[1]));

	if (bind(x, (struct sockaddr *)&addr, sizeof(addr)) == -1)
	{
		perror("server: bind");
		return 1;
	}
	if (listen(x, 5) == -1)
	{
		perror("server: listen");
		return 1;
	}

	printf("server start !!! \n");

	while (1)
	{
		clilen = sizeof(cli_addr);

		if ((y = accept(x, (struct sockaddr *)&cli_addr, &clilen)) == -1)
		{
			perror("server: accept");
			continue;
		}

		inet_ntop(AF_INET, &cli_addr.sin_addr, buf, sizeof(buf)); // client address
		printf("client address => %s\n", buf);

		pid = fork();

		if (pid == -1)
		{
			close(y);
			continue;
		}
		fork_num++;

		if (pid == 0) //자식
		{
			close(x);
			while (1)
			{
				if (fork_num == 1)
				{
					str_len = read(y, buffer, BUFSIZ);
					printf("receive message1: %s\n", buffer);
					if (i <= 20)
					{
						dis[i] = atoi(buffer);
						i++;
					}
					if (i == 20)
					{
						sp = speed(dis);
						sprintf(message, "%f", sp);
						write(fd1[1], message, sizeof(message));
						strcpy(message, "\0");
					}
					if (atoi(buffer) == 0)
					{
						i = 0;
					}
					bu1 = atoi(buffer);
					order(buffer);
					write(y, buffer, sizeof(buffer));
					order2(buffer, bu1, bu);
					write(y, buffer, sizeof(buffer));
					bu = bu1;
				}
				else
				{
					read(fd2[0], buffer, sizeof(buffer));
					write(y, buffer, sizeof(buffer));
					str_len = read(y, buffer, sizeof(buffer));
					printf("receive message2: %s\n", buffer);
					write(fd2[1], buffer, sizeof(buffer));
					read(fd2[0], buffer, sizeof(buffer));
					usleep(10);
					write(y, buffer, sizeof(buffer));
				}
			}
			close(y);
			puts("client disconnected...");
			return 0;
		}
		close(y);
		if (fork_num == 2)
		{
			while (1)
			{
				read(fd1[0], buffer, sizeof(buffer));
				sp = atof(buffer);
				write(fd2[1], buffer, sizeof(buffer));
				usleep(10);
				read(fd2[0], buffer, sizeof(buffer));
				red_order(buffer, sp);
				puts(buffer);
				write(fd2[1], buffer, sizeof(buffer));
			}
		}
	}
	close(x);
	return 0;
}