#include "common.h"
#include "sockwrap.h"
#include "readWrite.h"
#include "config.h"


#define convert(addr, sock) \
	sock.port = ntohs(addr.sin_port); \
	inet_ntop(AF_INET, &addr.sin_addr, sock.ip, 15);

void acceptSocket(int);
void doClient(int);

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

void doClient(int clientfd) {
	char buf[MAXLine];
	for(; ;) {
		int size = readline2(clientfd, buf, MAXLine);
		if (size < 0) {
			Close(clientfd);
			exit(1);
		}
		fprintf(stdout, "Client: %s", buf);
		size = readline(STDIN_FILENO, buf, MAXLine);
		writen(clientfd, buf, size);
	}
}

void acceptSocket(int fd) {
	struct sockaddr_in clientAddr;
	socklen_t len;
	for ( ; ;) {
		int clientfd = Accept(fd, (SADDR*)&clientAddr, &len);
		SocketAddr client;
		convert(clientAddr, client);
		fprintf(stdout, "Client: ip %s, port %d\n", client.ip, client.port);
		pid_t child;
		if ((child = fork()) == 0) {
			Close(fd);
			doClient(clientfd);
		}
		else
			Close(clientfd);
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