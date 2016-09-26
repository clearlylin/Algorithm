#include "common.h"
#include "tcpWrap.h"
#include "readWrite.h"
#include "config.h"

void server01(int port, in_addr_t ip) {
	int listenfd, clientfd;
	socklen_t len;
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0) {
		fprintf(stderr, "%s\n", "socket failed");
		return;
	}
	struct sockaddr_in servaddr, client, server01;
	len = sizeof(servaddr);
	bzero(&servaddr, len);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = ip;
	servaddr.sin_port = htons(port);

	Bind(listenfd, (struct sockaddr*)&servaddr, len);

	Listen(listenfd, LISTENNQ);

	getsockname(listenfd, (struct sockaddr*)&server01, &len);
	char ipStr[20];
	fprintf(stdout, "Server  IP: %s, PORT:%d\n",
			inet_ntop(AF_INET, &server01.sin_addr, ipStr, 20),
			ntohs(server01.sin_port));

	for(;;) {
		printf("Waiting Client\n");
		clientfd = Accept(listenfd, (struct sockaddr*)&client, &len);
		fprintf(stdout, "ip: %s, port: %d\n",
			inet_ntop(AF_INET, &client.sin_addr, ipStr, 20),
			ntohs(client.sin_port));

		fprintf(stdout, "Server:%s\n", "Waiting Reading");
		readline(clientfd, ipStr, 20);
		fprintf(stdout, "Client:%s\n", ipStr);

		fprintf(stdout, "Server: %s\n", "Ready Write");
		snprintf(ipStr, 20, "%s\n", "Hello client");
		writen(clientfd, ipStr, strlen(ipStr));

		Close(clientfd);
	}
}

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		fprintf(stdout, "%s\n", "ip, port");
		return 1;
	}

	int port = atoi(argv[1]);
	printf("%s\n", argv[2]);
	in_addr_t ip = inet_addr(argv[2]);
	server01(port, ip);
	return 0;
}
