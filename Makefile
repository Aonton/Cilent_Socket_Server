# Make File for Server & Client Project
# Amy Feng
# April 7, 2018
# How to use this make file
# OPTION:
# 1) type "make all" on the command line
# Purpose: This will build/compile the server.c
# and client.c files. Then to run the programs,
# run their executables.
# ./server and ./client
# *** Note: You must start the server before the client ***
# 2) type "make clean"
# Purpose: removes object files. Sometimes it is needed to
# remove the object files so taht you code runs with the
# newest code changes. 

CC = gcc
CFLAGS = -c

all: client server

server: server.o
	$(CC) server.o -o server
client: client.o
	$(CC) client.o -o client
server.o: server.c
	$(CC) $(CFLAGS) server.c
client.o: client.c
	$(CC) $(CFLAGS) client.c
clean:
	rm -rf *.o
