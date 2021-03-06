#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include "executor.h" //Added
#include <stdbool.h>

#define PORT 4444

/* Amy Feng
	April 7, 2018
	Credit for starting the socket code goes to:
	Nikhil Tomar
	url: https://github.com/nikhilroxtomar/Multiple-Client-Server-Program-in-C-using-fork/blob/master/tcpServer.c
*/

int main(){
	FILE* cmd_output;

	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024];
	pid_t childpid;
	bool waitingForPassword = true;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", 4444);

	if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		printf("[-]Error in binding.\n");
	}


	while(1){
		newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
		if(newSocket < 0){
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				recv(newSocket, buffer, 1024, 0);
				if(waitingForPassword)
				{
					printf("Password Received\n");
				}

				if(strcmp(buffer, ":exit\n") == 0){
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}
				else if((strcmp(buffer, "Welcome123") == 0) && waitingForPassword)
				{
					printf("Password okay\n");
					waitingForPassword = false;
				}
				else{
					printf("Command received from client: %s", buffer);
					printf("Executing command...\n");
					cmd_output = (FILE *) executor(buffer);






					// char client_receive[1];
					// char server_send[1];
					// server_send[0] = '`';

					// recv(newSocket, client_receive, 1, 0);
					// while(client_receive[0] != '!')
					// {
  			// 			send(newSocket, server_send, 1, 0); //acknowledge to client
  			// 			recv(newSocket, client_receive, 1, 0);
					// }

					// bzero(client_receive, 1);
					// bzero(server_send, 1);







					while (fgets(buffer, sizeof buffer, cmd_output) != NULL)
					{
						send(newSocket, buffer, strlen(buffer), 0);
					}

					bzero(buffer, sizeof(buffer));
					buffer[0] = '\0';
					send(newSocket, buffer, 1, 0);

					printf("Sent command output to client\n\n");

					bzero(buffer, sizeof(buffer));
				}
			}
		}

	}

	close(newSocket);


	return 0;
}
