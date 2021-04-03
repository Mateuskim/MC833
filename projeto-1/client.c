#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int loginIntoServer(int clientSocket){
	char buffer[MAXLINE];

	int answer;
	printf("[+] Email:");
	fgets(buffer, MAXLINE, stdin);
	send(clientSocket, buffer, MAXLINE, 0);

	if (recv(clientSocket, buffer, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("Server terminated prematurely");
        exit(0);
    }
	answer = atoi(buffer);

	return answer;
}

void gettingMenuFromServer(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int menuSize, i;

	// Receiving size of menu
	if (recv(clientSocket, buffer, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("Server terminated prematurely");
        exit(0);
    }
	menuSize = atoi(buffer);

	// Receiving and printing menu to client
	for(i = 1; i <= menuSize; i++){
		if (recv(clientSocket, buffer, MAXLINE,0) == 0){
			//error: server terminated prematurely
			perror("Server terminated prematurely");
			exit(0);
    	}
		printf("(%d) - %s", i, buffer);
	}
	printf("\nChoose an action:");

}

void startService( int clientSocket){
 

	// Auxiliar variables
	char buffer[MAXLINE];
	int i;

	bzero(buffer, MAXLINE);
	
	// Starting service
	while(1){
		printf("[+] Actions:\n");
		gettingMenuFromServer(clientSocket);

		// Get action to be executed [1-8]
		fgets(buffer, MAXLINE, stdin);
		send(clientSocket, buffer, strlen(buffer), 0);

		if(read(clientSocket, buffer, MAXLINE) < 0){
			perror("\n[-] Client:::Server Terminated permanently\n");
			exit(EXIT_FAILURE);
		}else{
			printf("[+] Received Message from the Server is: %s\n", buffer);
		}
	}

}

void main(){
	
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[MAXLINE];
	char data[MAXLINE];

	int login = 0;


	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(clientSocket<0){
		printf("[-] Fail to create the Socket\n");
		return;
	}
	printf("[+] Client Socket Created Sucessfully.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))<0){
		perror("[-] Connection Error");
		// close(clientSocket);
		exit(EXIT_FAILURE);
	}
	printf("[+] Connected to Server.\n");
	if(loginIntoServer(clientSocket))
		startService(clientSocket);
	else
		printf("[-] User not found");

}