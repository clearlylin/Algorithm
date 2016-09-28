
depend = ../log.o ../sockwrap.o ../readWrite.o
DEBUG = -g -O0

all: client server

client: client.c
	gcc -o client client.c -I../ $(depend) $(DEBUG)

server: server.c
	gcc -o server server.c  -I../ $(depend) $(DEBUG)

clean:
	rm client server
