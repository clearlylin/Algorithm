#include "sockwrap.h"
#include "log.h"

int Socket(int family, int type, int protocol) {
	int fd = socket(family, type, protocol);
	if (fd < 0)
		err_msg("socket failed \n");
	return fd;
}

void Connect(int sockfd, const struct sockaddr* servaddr, socklen_t addrlen) {
	if (connect(sockfd, servaddr, addrlen) < 0)
		err_quit("connect failed\n");
}

void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
	if (bind(sockfd, addr, addrlen) < 0)
		err_quit("bind failed\n");
}

void Listen(int sockfd, int backlog) {
	if (listen(sockfd, backlog) < 0)
		err_quit("listen failed\n");
}

int Accept(int sockfd, struct sockaddr* clientAddr, socklen_t* addrlen) {
	int fd = accept(sockfd, clientAddr, addrlen);
	if (fd < 0)
		err_quit("accept failed\n");
	return fd;
}

int Close(int sockfd) {
	if(close(sockfd) < 0)
		err_msg("close failed\n");
}

void SetSock(struct sockaddr_in* sock, int port, const char* strIp) {
	in_addr_t ip = inet_addr(strIp);

	socklen_t len = sizeof(struct sockaddr_in);
	bzero(sock, len);
	sock->sin_family = AF_INET;
	sock->sin_port = htons(port);
	sock->sin_addr.s_addr = ip;
}


void getSoketAddr(int fd, SocketAddr* sock) {
	if (!sock) {
		err_msg("sock is NULL");
		return;
	}
	struct sockaddr_in client;
	socklen_t len;
	getsockname(fd, (SADDR*)&client, &len);
	inet_ntop(AF_INET, &client.sin_addr, sock->ip, 15);
	sock->port = ntohs(client.sin_port);
}
