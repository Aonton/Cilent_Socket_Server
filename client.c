#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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

	clock_t start, end;
	double cpu_time_used;
	int total_bits;

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
		fgets(buffer,100,stdin);
		send(clientSocket, buffer, strlen(buffer), 0);


		usleep(100 * 1000);

		start = clock(); // end the process timer


	// char send_client[1];
	// send_client[0] = '!';
	// char receive_server[1];

	// while(receive_server[0] != '`')
	// {
	// 	send(clientSocket, send_client, 1, 0);
	// 	recv(clientSocket, receive_server, 1, 0);
	// }

	// bzero(send_client, 1);
	// bzero(receive_server, 1);

		if(strcmp(buffer, ":exit") == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
			break;
		}

		char output[1024];
		char output_buffer[1024];
		int n;

		n = recv(clientSocket, output_buffer, sizeof(output_buffer), 0);
		total_bits += n * 8; // recv is the length of the message, multiple the length by 8 to get the bits of the message
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
				total_bits += n * 8; // recv is the length of the message, multiple the length by 8 to get the bits of the message
			}
			else {
				break;
			}
		}

	end = clock(); // End the process timer
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000; // Convert from seconds to milliseconds

	printf("%s\n", output);
	printf("Process Took %f milliseconds\n", cpu_time_used);
	printf("Average Throughput of %f kilobytes per second \n\n", ((double) total_bits / 8000) / (((double) (end - start) / CLOCKS_PER_SEC))); // Divided by 8000 to get kilobytes

	bzero(output, sizeof(output));


		// if(recv(clientSocket, buffer, 1024, 0) < 0){
		// 	printf("[-]Error in receiving data.\n");
		// 	bzero(buffer, sizeof(buffer));
		// }else{

		// 	//clearScreen();
		// printf("%s\n", buffer);
		// 	bzero(buffer, sizeof(buffer));
		// }
}

return 0;
}
