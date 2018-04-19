#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

/* Amy Feng
	April 7, 2018
	Credit for starting the socket code goes to:
	Nikhil Tomar
	url: https://github.com/nikhilroxtomar/Multiple-Client-Server-Program-in-C-using-fork/blob/master/tcpServer.c
*/

int main(){

	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Client Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Connected to Server.\n");

	while(1){
		printf("Remote Shell$ ");
		//scanf("%s", buffer);//&buffer[0]);
		fgets(buffer,100,stdin);
		send(clientSocket, buffer, strlen(buffer), 0);

		usleep(100 * 1000);

		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}

		char output[1024];
		char output_buffer[1024];
		int n;

		n = recv(clientSocket, output_buffer, sizeof(output_buffer), 0);
		while(n > 0) {

			int stop = 0;

			for (int i = 0; i <= sizeof(output_buffer); i++) {	
				if (output_buffer[i] == '\0') {
					strncat(output, output_buffer, n);
					stop = 1;
					break;
				}
			}



			if(n > 0 && stop == 0) {
				strncat(output, output_buffer, n);
				n = recv(clientSocket, output_buffer, sizeof(output_buffer), 0);
			}
			else {
				break;
			}
		}

	printf("%s\n", output);
	bzero(output, sizeof(output));


		// if(recv(clientSocket, buffer, 1024, 0) < 0){
		// 	printf("[-]Error in receiving data.\n");
		// 	bzero(buffer, sizeof(buffer));
		// }else{

		// 	//clearScreen();
		// 	printf("%s\n", buffer);
		// 	bzero(buffer, sizeof(buffer));
		// }
	}

	return 0;
}
