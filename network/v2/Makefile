
depend = ../log.o ../sockwrap.o ../readWrite.o

all: client server

client: client.c
	gcc -o client client.c -I../ $(depend)

server: server.c
	gcc -o server server.c  -I../ $(depend)

clean:
	rm client server
