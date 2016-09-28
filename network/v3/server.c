#include "common.h"
#include "sockwrap.h"
#include "readWrite.h"
#include "config.h"


void convert(struct sockaddr_in* client, SocketAddr* addr) {
	addr->port = ntohs(client->sin_port);
	inet_ntop(AF_INET, &client->sin_addr, addr->ip, 15);
}

void acceptSocket(int);
void doClient(SocketAddr*, int);

void initSocket(const char* strPort, const char* ip) {
	int port = atoi(strPort);
	struct sockaddr_in servaddr;
	SetSock(&servaddr, port, ip);

	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	Bind(fd, (SADDR*)&servaddr, sizeof(SADDR));
	Listen(fd, LISTENNQ);

	fprintf(stdout, "%s\n", "acceptSocket");
	acceptSocket(fd);
}

void doClient(SocketAddr* client, int clientfd) {
	char buf[MAXLine];
	fcntl(clientfd, F_SETFL, O_NONBLOCK);
	fcntl(STDOUT_FILENO, F_SETFL, O_NONBLOCK);
	fprintf(stdout, "Client: ip %s, port %d\n", client->ip, client->port);
	for(; ;) {
		int size = readline2(clientfd, buf, MAXLine);
		if (errno != EAGAIN && size < 0) {
			free(client);
			Close(clientfd);
			exit(1);
		}
		if (size > 0)
			fprintf(stdout, "%s: %s\n", client->ip, buf);
		size = readline2(STDIN_FILENO, buf, MAXLine);
		if (size > 0) {
			writen(clientfd, buf, size);
		}
		sleep(2);
	}
}

void sig_children(int signo) {
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		fprintf(stdout, "child %d terminated\n", pid);
}

void acceptSocket(int fd) {
	struct sockaddr_in clientAddr;
	socklen_t len;
	int connfd;
	signal(SIGCHLD, sig_children);
	for ( ; ;) {
		connfd = Accept(fd, (SADDR*)&clientAddr, &len);
		if (connfd == 0)
			continue;
		SocketAddr* sockaddr = (SocketAddr*)malloc(sizeof(SocketAddr));
		convert(&clientAddr, sockaddr);
		pid_t child;
		if ((child = fork()) == 0) {
			Close(fd);
			doClient(sockaddr, connfd);
		}
		else
			Close(connfd);
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
