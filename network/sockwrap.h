#include "common.h"

int Socket(int family, int type, int protocol);

void Connect(int sockfd, const struct sockaddr* servaddr, socklen_t addrlen);

void Bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr* clientAddr, socklen_t* addrlen);

int Close(int sockfd);

void SetSock(struct sockaddr_in* sock, int port, const char* strIp);


typedef struct SocketAddr {
	int port;
	const char* ip;
	void (*free)(struct SocketAddr* ptr);
} SocketAddr;


SocketAddr* getSoketAddr(int fd);

