
depend = ../log.o ../tcpWrap.o ../readWrite.o

all: client server

client: client.c
	gcc -o client client.c -I../ $(depend)

server: server.c
	gcc -o server server.c  -I../ -L../ $(depend)

clean:
	rm client server
