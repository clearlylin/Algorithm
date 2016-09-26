#include "readWrite.h"
#include "config.h"

uint32_t readn(int fd, void* buf, uint32_t size) {
	uint32_t left = size, has;
	char* ptr = buf;
	while(left > 0) {
	    if ((has = read(fd, ptr, size)) < 0) {
	    	if (errno != EINTR)
	    		return -1;
	    	has = 0;
	    	continue;
	    }
	    else if(has == 0)
	    	break;
	    left -= has;
	    ptr += has;
	}
	return size - left;
}
//Efficiency is relatively low
//maybe can use buffer.
uint32_t readline(int fd, void* buf, uint32_t size) {
	uint32_t left = size, has;
	char c, *ptr = buf;
	while(left > 0) {
	    if ((has = read(fd, &c, 1)) < 0) {
	    	if (errno != EINTR)
	    		return -1;
	    	has = 0;
	    	continue;
	    }
	    else if(has == 0)
	    	return size - left;
	    left -= 1;
	    *ptr++ = c;
	    if (c == '\n')
	    	return size - left;
	}
}

//provide buffer, but not threading security

static char buf[MAXLine];
static int buf_size = 0;
static int read_size = 0;
static int read_Char(int fd, char* c) {
	if (buf_size <= 0) {
		read_size = 0;
Again:
		buf_size = read(fd, buf, MAXLine);
		if (buf_size < 0) {
			if (errno != EINTR)
				return -1;
			buf_size = 0;
			goto Again;
		}
		else if(buf_size == 0)
			return 0;
	}
	*c = buf[read_size++];
	--buf_size;
	return 1;
}

uint32_t readline2(int fd, void* buf, uint32_t size) {
	char c, *ptr = buf;
	int ret, i = 1;
	for(; i <= size; ++i) {
		if ((ret = read_Char(fd, &c)) < 0)
			return -1;
		else if(ret == 0)
			return i;
		*ptr++ = c;
		if (c == '\n')
			return i;
	}
	return size;
}

uint32_t writen(int fd, void* buf, uint32_t size) {
	uint32_t left, writes;
	char* ptr = buf;
	left = size;
	while(left > 0) {
		if ((writes = write(fd, ptr, size)) <= 0) {
			if (writes < 0 && errno == EINTR) {
				writes = 0;
				continue;
			}
			else
				return -1;
		}
		left -= writes;
		ptr += writes;
	}
	return size;
}