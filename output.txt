# Make File for Server & Client Project

CC = gcc
CFLAGS = -c

all: client server executor

server: server.o
	$(CC) server.o -o server
client: client.o
	$(CC) client.o -o client
executor: executor.o
	$(CC) executor.o -o executor
server.o: server.c
	$(CC) $(CFLAGS) server.c
client.o: client.c
	$(CC) $(CFLAGS) client.c
executor.o: executor.c
	$(CC) $(CFLAGS) executor.c
clean:
	rm -rf *.o
