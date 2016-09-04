#include "net.h"


#include <errno.h>

static void do_error(char *msg) {
	fprintf(stderr, "%s\n", msg);
}

int server_proc(const char* addr, int port) {
	int fd;
	SockAddr  servAddr;
	fd = sock(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == -1) {
		do_error("sock error");
		return -1;
	}
	bzero(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, addr, &servAddr.sin_addr);
	servAddr.sin_port = htons(port);

	if (bind(fd, (SockAddr*)&servAddr, sizeof(servAddr)) == -1) {
		do_error("bind error");
		return -1;
	}
	char *ptr;
	int backlog = 5;
	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if (listen(fd, backlog) < 0 ) {
		do_error("listen error");
		return -1;
	}
	return fd;
}

int server_accept(int srvfd) {
	SockAddr cltaddr;
	socklen_t cltlen;
	cltlen = sizeof(cltaddr);
	int cltfd = -1;

ACCEPT:
	cltfd = accept(srvfd, (SockAddr*)&cltaddr, &cltlen);

	if (cltfd == -1) {
		if (errno == EINTR)
			goto ACCEPT;
		else {
			do_error("accept error");
			return -1;
		}
	}

}