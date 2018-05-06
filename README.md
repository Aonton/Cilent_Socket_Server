Members: Amy Feng, Kevin Ho, Saul Soto
Date: 4/21/18
Project ID:
CS Class: CS3595
Programming Language: C
OS/Hardware dependencies: Unix, gcc

Problem Description: Our program consists of three different parts: a server, a client, and an executor. The program is tasked with initiating a socket server that establishes a two-way connection with a client, where messages can be sent and received. Users are able to enter various UNIX commands (that do not use stdin) on the client, and these are subsequently sent to the server. Once having received a command, the server takes it and passes the command to the executor method, that then runs it, stores its output in a buffer, and passes that buffer to the server, where it is then sent back to the client. Once the client receives this buffer, it is printed, and the user is left able to enter another command.

* Nikhil Tomar, a programmer on the Github platform, is the author of most of the server and client code used in our project.

How to build the program:
Once having downloaded the project files to a separate folder, inside that folder, run the command "make clean" on the command-line.
        Then run the command "make" or "make all" (OSX might not allow "make all")
After completing these two steps, you should now be able to run the server and client by entering the commands: "./server" and "./client"
* It is important that you run these two commands in this order and in separate windows because the server must first be run before the client is initialized and because the server and client will not work in the same window.

After having run the server and the client, you should now able to enter a command (that does not use stdin) on the client-side and see its output (once the program is done working its magic).

Example run:

Remote Shell$ cat Makefile
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
# remove the object files so that you code runs with the
# newest code changes. 

CPP = g++
CC = gcc
CFLAGS = -c

all: client server

server: server.o
	$(CC) server.o executor.c -o server
client: client.o
	$(CC) client.o -o client
server.o: server.c
	$(CC) $(CFLAGS) server.c
client.o: client.c
	$(CC) $(CFLAGS) client.c
clean:
	rm -rf *.o
	rm logfile.txt

Process Took 0.054000 milliseconds
Average Throughput of 14629.629630 kilobytes per second 


