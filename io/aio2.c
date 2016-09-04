#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include <fcntl.h>
#include <aio.h>
#include <unistd.h>

#define BUFF_SIZE 1024

void read_notify(sigval_t sigval) {
        struct aiocb* cb = (struct aiocb*)sigval.sival_ptr;
        if( aio_error(cb) != 0 ) {
                fprintf(stderr, "aio_error: %s/n", strerror(errno));
                return;
        }
        int len = aio_return(cb);
        if( len < 0 ) {
                fprintf(stderr, "aio_return error: %s/n", strerror(errno));
                return;
        }
        write(STDOUT_FILENO, (void*)cb->aio_buf, len);
        exit(0);
}

int main(int argc, char **argv)
{
        if (argc != 2 ) {
                fprintf(stderr, "usage:%s filename/n", argv[0]);
                return -1;
        }
        const char* filename = argv[1];
        int fd = open(filename, O_RDONLY);
        if (fd < 0 ) {
                fprintf(stderr, "open %s error: %s/n", filename, strerror(errno));
                return -1;
        }
        char data_buf[BUFF_SIZE];
        struct aiocb iocb;
        bzero(&iocb, sizeof(struct aiocb));
        iocb.aio_fildes = fd;
        iocb.aio_offset = 0;
        iocb.aio_buf = data_buf;
        iocb.aio_nbytes = BUFF_SIZE;
        iocb.aio_sigevent.sigev_notify = SIGEV_THREAD;
        iocb.aio_sigevent.sigev_notify_function = read_notify;
        iocb.aio_sigevent.sigev_value.sival_ptr = &iocb;
        //initiate read
        if( aio_read(&iocb) < 0) {
                fprintf(stderr, "aio_read error: %s/n", strerror(errno));
                return -1;
        }
        pause();
        close(fd);
        return 0;
}