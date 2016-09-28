#include "common.h"
#include "sockwrap.h"
#include "readWrite.h"
#include "config.h"

void sendMsg(int);
void receiveMsg(int);

void sig_children(int signo) {
	pid_t child;
	int stat;
	while((child = waitpid(-1, &stat, WNOHANG)) > 0)
		fprintf(stdout, "child %d terminated\n", child);
}

void initSocket(const char* strPort, const char* strIP) {
	int port = atoi(strPort);
	struct sockaddr_in servaddr;
	SetSock(&servaddr, port, strIP);

	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	Connect(fd, (SADDR*)&servaddr, sizeof(servaddr));

	SocketAddr addr;
	getSoketAddr(fd, &addr);
	fprintf(stdout, "Bind IP:%s, PORT:%d\n", addr.ip, addr.port);

	signal(SIGCHLD, sig_children);

	pid_t child;
	if ((child = fork()) == 0)
		sendMsg(fd);
	else
		receiveMsg(fd);
}

void sendMsg(int fd) {
	char buf[MAXLine];
	for(;;) {
		uint32_t size = readline(STDIN_FILENO, buf, MAXLine);
		if (size < 0) {
			Close(fd);
			exit(0);
		}
		else if(size > 0)
			writen(fd, buf, size);
	}
}

void receiveMsg(int fd) {
	char buf[MAXLine];
	for(;;) {
		uint32_t size = readline2(fd, buf, MAXLine);
		if (size < 0) {
			Close(fd);
			exit(0);
		}
		else
			fprintf(stdout, "Server: %s\n", buf);
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		fprintf(stdout, "%s\n", "input args port ip");
		return 0;
	}
	initSocket(argv[1], argv[2]);

	return 0;
}