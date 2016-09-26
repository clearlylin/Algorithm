#include "tcpWrap.h"
#include "readWrite.h"
#include "common.h"

void client(int port, in_addr_t ip) {
	int fd = Socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		fprintf(stderr, "%s\n", "socket failed");
		return;
	}
	struct sockaddr_in servaddr, client;
	socklen_t len = sizeof(servaddr), lent;
	bzero(&servaddr, len);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	servaddr.sin_addr.s_addr = ip;
	Connect(fd, (struct sockaddr*)&servaddr, len);

	getsockname(fd, (struct sockaddr*)&client, &lent);
	char ipStr[20];
	fprintf(stdout, "Bind IP: %s, PORT:%d\n",
		inet_ntop(AF_INET, &client.sin_addr, ipStr, 20),
		ntohs(client.sin_port));

	snprintf(ipStr, 20, "%s\n", "Hello Server");
	writen(fd, ipStr, strlen(ipStr));
	fprintf(stdout, "Client:%s\n", "Write Completed");

	readline(fd, ipStr, 20);
	fprintf(stdout, "Server:%s\n", ipStr);
	sleep(20);
}


int main(int argc, char const *argv[])
{
	if (argc != 3) {
		fprintf(stdout, "%s\n", "ip, port");
		return 1;
	}

	int port = atoi(argv[1]);
	const char* ips = argv[2];
	in_addr_t ip = inet_addr(ips);
	client(port, ip);
	return 0;
}