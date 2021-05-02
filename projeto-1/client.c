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

/*
 * Function:  sendToServer 
 * --------------------
 * Send a generic message to server
 *
 *  clientSocket: self-explanatory
 *  buffer : message to be sent
 *
 */
void sendToServer(int clientSocket, char* buffer){
	// Auxiliar variables
	send(clientSocket, buffer, MAXLINE, 0);
}

/*
 * Function:  sendIntToServer 
 * --------------------
 * Send a integer variable to server
 *
 *  clientSocket: self-explanatory
 *  n : integer to be sent
 *
 */
void sendIntToServer(int clientSocket, int n){
	// Auxiliar variable
	char buffer[MAXLINE];

    snprintf(buffer, MAXLINE, "%d", n);
    sendToServer(clientSocket, buffer);
}

/*
 * Function:  getAndSendToServer 
 * --------------------
 * Read input from client and send it to server
 *
 *  clientSocket: self-explanatory
 *
 */
void getAndSendToServer(int clientSocket){
	// Auxiliar variable
	char buffer[MAXLINE];

	fgets(buffer, MAXLINE, stdin);
	buffer[strlen(buffer)-1] = '\0';
	sendToServer(clientSocket, buffer);
}

/*
 * Function:  readFromServer 
 * --------------------
 * Read response from server
 *
 *  clientSocket: self-explanatory
 *  buffer: Variable to store response from server
 *
 */
void readFromServer(int clientSocket, char* buffer){
	if(read(clientSocket, buffer, MAXLINE) < 0){
		perror("\n[-] Client:::Server Terminated permanently\n");
		exit(EXIT_FAILURE);
	}
	
}


/*
 * Function:  sendToAndReadFromServer 
 * --------------------
 * Read input from client, send to server and read response from server
 *
 *  clientSocket: self-explanatory
 *  buffer: Variable to store response from server
 *
 */
void sendToAndReadFromServer(int clientSocket, char* buffer){
	getAndSendToServer(clientSocket);
	readFromServer(clientSocket, buffer);
}

/*
 * Function:  loginIntoServer 
 * --------------------
 * Get email and send to server
 *
 *  clientSocket: self-explanatory
 * 
 *  returns:
 * 		1 - if user is root
 * 		0 - if user exists but is not root
 * 		-1 - if user doesn't exists
 */
int loginIntoServer(int clientSocket){
	char buffer[MAXLINE];
	int answer;
	printf("[+] Email:");
	sendToAndReadFromServer(clientSocket, buffer);
	answer = atoi(buffer);

	printf("\n=============== Response =====================\n");
	if(answer>=0){
		printf("Login Successfully!");
		printf("\n==============================================\n");
	}
	return answer;
}

/*
 * Function:  gettingMenuFromServer 
 * --------------------
 * get menu from server and show to client
 * 
 *  clientSocket: self-explanatory
 *
 */
void gettingMenuFromServer(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int menuSize, i;

	printf("[+] Actions:\n");
	// Receiving size of menu
	readFromServer(clientSocket, buffer);
	menuSize = atoi(buffer);

	// Receiving and printing menu to client
	for(i = 1; i <= menuSize; i++){
		readFromServer(clientSocket, buffer);
		printf("(%d) - %s", i, buffer);
	}
	printf("\nChoose an action:");

}

/*
 * Function:  listUsersByCourse 
 * --------------------
 * get list of users by course and show to client
 * 
 *  clientSocket: self-explanatory
 *
 */

void listUsersByCourse(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i;

	// Variable to store number of users found on the search
	int numberOfUsers;
	
	printf("Listing users by course.\nCourse:");
	sendToAndReadFromServer(clientSocket, buffer);

	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);

	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nNumber of users found:%d\n", numberOfUsers);
		// Receiving and printing users
		for (i = 0; i < numberOfUsers; i++){
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
		}
	}else{
		printf("No user found for this course!\n");
	}
	printf("\n==============================================\n");

	

}

/*
 * Function:  listUsersBySkill 
 * --------------------
 * get list of users by skill and show to client
 * 
 *  clientSocket: self-explanatory
 *
 */

void listUsersBySkill(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i;

	// Variable to store number of users found on the search
	int numberOfUsers;
	
	printf("Listing users by Skill.\n");
	printf("Skill:");
	sendToAndReadFromServer(clientSocket, buffer);

	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);

	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nNumber of users found:%d\n", numberOfUsers);
		// Receiving and printing users
		for (i = 0; i < numberOfUsers; i++){
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			printf("\n");
		}
	}else{
		printf("No user found for this skill!\n");
	}
	printf("\n==============================================\n");

	

}

/*
 * Function:  listUsersByYear 
 * --------------------
 * get list of users by graduation year and show to client
 * 
 *  clientSocket: self-explanatory
 *
 */

void listUsersByYear(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i;

	// Variable to store number of users found on the search
	int numberOfUsers;
		
	printf("Listing users by Skill.\n");
	printf("Graduation year:");
	sendToAndReadFromServer(clientSocket, buffer);

	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);

	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nNumber of users found:%d\n", numberOfUsers);
		// Receiving and printing users
		for (i = 0; i < numberOfUsers; i++){
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
		}
	}else{
		printf("No user found for this year!\n");
	}
	printf("\n==============================================\n");

}

/*
 * Function:  listUsers 
 * --------------------
 * get list of all users and show to client
 * 
 *  clientSocket: self-explanatory
 *
 */
void listUsers(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i;

	// Variable to store number of users
	int numberOfUsers;
	
	printf("Listing all Users.\n");
	readFromServer(clientSocket, buffer);
	
	// Buffer returns number of users
	numberOfUsers = atoi(buffer);
	
	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nNumber of users found:%d\n", numberOfUsers);
		// Receiving and printing users
		for (i = 0; i < numberOfUsers; i++){
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
		}
	}else{
		printf("No user found!\n");
	}
	printf("\n==============================================\n");

}

/*
 * Function:  listUserByEmail 
 * --------------------
 * Show info of the client searched
 * 
 *  clientSocket: self-explanatory
 *
 */
void listUserByEmail(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i, j, n;

	// Variable to store number of users
	int numberOfUsers;
	
	// Getting response from server
	printf("Showing info of user by email.\nEmail:");
	sendToAndReadFromServer(clientSocket, buffer);

	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);
	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nUser Found!\n");
		// Receiving and printing users
		for (i = 0; i < numberOfUsers; i++){
			
			// Reading email
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			
			// Reading name
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);

			// Reading city
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);

			// Reading course
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);
			
			// Reading year of graduation
			readFromServer(clientSocket, buffer);
			printf("%s\n", buffer);


			// Reading number of skills
			readFromServer(clientSocket, buffer);

			n = atoi(buffer);
			for(j = 0 ; j < n ; j++){
				// Reading skills
				readFromServer(clientSocket, buffer);
				printf("%s\n", buffer);
			}

			// Reading number of experiences
			readFromServer(clientSocket, buffer);
			n = atoi(buffer);
			for(j = 0 ; j < n ; j++){
				// Reading experiences
				readFromServer(clientSocket, buffer);
				printf("%s\n", buffer);
			}

		}
	}else{
		printf("No user found for this email!\n");
	}
	printf("\n==============================================\n");

}


/*
 * Function:  removeUserByEmail 
 * --------------------
 * remove user
 * 
 *  clientSocket: self-explanatory
 *
 */
void removeUserByEmail(int clientSocket){


	// Auxiliar variable
	char buffer[MAXLINE];

	// Variable to store number of users
	int numberOfUsers;

	printf("Removing user.\nEmail:");

	sendToAndReadFromServer(clientSocket, buffer);

	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);

	printf("\n=============== Response =====================\n");
	if(numberOfUsers){
		printf("\nUser Found! Deleting ...\n");
		readFromServer(clientSocket, buffer);
		printf("%s\n", buffer);
		// Receiving and printing users
		
	}else{
		printf("No user found for this email!\n");
	}
	printf("\n==============================================\n");

}

/*
 * Function:  addExperienceUser 
 * --------------------
 * add experience to user
 * 
 *  clientSocket: self-explanatory
 *
 */
void addExperienceUser(int clientSocket){

	// Auxiliar variable
	char buffer[MAXLINE];

	// Variable to store number of users
	int numberOfUsers;


	printf("Adding experience in User.\nEmail:");
	sendToAndReadFromServer(clientSocket, buffer);
	
	// Buffer returns number of users found
	numberOfUsers = atoi(buffer);



	
	if(numberOfUsers){
			// Getting skill to be added
		printf("\nSkill to add:");	
		getAndSendToServer(clientSocket);
		readFromServer(clientSocket, buffer);
		printf("\n=============== Response =====================\n");
		printf("%s\n", buffer);
		
		// Receiving and printing users
	}else{
		printf("\n=============== Response =====================\n");
		printf("No user found for this email!\n");
	}
	printf("\n==============================================\n");

}

/*
 * Function:  addNewUser 
 * --------------------
 * add new user in the platform
 * 
 *  clientSocket: self-explanatory
 *
 */
void addNewUser(int clientSocket){

	// Auxiliar variables
	char buffer[MAXLINE];
	int i, j, numberOfUsers, n;
	
	// Variable to store response from server confirming if
	// the users was created
	int user_created = 0;


	printf("Add new user\n");
	printf("Email:");

	// Getting email from client to be add
	getAndSendToServer(clientSocket);

	// Getting answer from server
	readFromServer(clientSocket, buffer);
	printf("\n%s\n", buffer);

	// Getting number of users found
	readFromServer(clientSocket, buffer);
	numberOfUsers = atoi(buffer);
	printf("number:%s\n", buffer);
	
	// If doesn't exists user with email
	if(!numberOfUsers){
		printf("First Name: ");	
		getAndSendToServer(clientSocket);
		printf("Last Name: ");	
		getAndSendToServer(clientSocket);
		printf("City: ");	
		getAndSendToServer(clientSocket);
		printf("Course: ");	
		getAndSendToServer(clientSocket);
		printf("Graduation year: ");	
		getAndSendToServer(clientSocket);

		printf("Number of Skills: ");
		fgets(buffer, MAXLINE, stdin);
		sendToServer(clientSocket, buffer);

		n = atoi(buffer);
		for (i = 1 ; i <= n ; i++){
			printf("Skill %d: ", i);
			getAndSendToServer(clientSocket);
		}

		printf("Number of Experiences: ");
		fgets(buffer, MAXLINE, stdin);
		sendToServer(clientSocket, buffer);
		
		n = atoi(buffer);
		for (i = 1 ; i <= n ; i++){
			printf("Skill %d: ", i);
			getAndSendToServer(clientSocket);
		}
		readFromServer(clientSocket, buffer);
		user_created = atoi(buffer);
		if(user_created){
			printf("User created successfully\n");
		}else{
			printf("User creation failed!\n");
		}

	}else{
		printf("User already exists!!\n\n");
	}

}
/*
 * Function:  executeCommand 
 * --------------------
 * execute command selected by client
 * 
 *  clientSocket: self-explanatory
 *  user: if user is (1)root  or (0)non-root
 *  command: command selected by client
 *
 */
void executeCommand(int clientSocket, int user, int command){
    if(user == 1){
        switch(command){
            case 1:
				addNewUser(clientSocket);
            break;
            case 2:
				addExperienceUser(clientSocket);
            break;
            case 3:
                listUsersByCourse(clientSocket);
            break;
            case 4:
				listUsersBySkill(clientSocket);
            break;
            case 5:
				listUsersByYear(clientSocket);
            break;
            case 6:
				listUsers(clientSocket);
            break;
            case 7:
				listUserByEmail(clientSocket);
            break;
            case 8:
                removeUserByEmail(clientSocket);
            break;
			case 9:
				exit(0);
            break;
        }

    }else{
        switch(command){
            case 1:
                listUsersByCourse(clientSocket);
            break;
            case 2:
				listUsersBySkill(clientSocket);
            break;
            case 3:
				listUsersByYear(clientSocket);
            break;
            case 4:
				listUsers(clientSocket);
            break;
            case 5:
				listUserByEmail(clientSocket);
            break;
			case 6:
				exit(0);
            break;
        }
    }
}
/*
 * Function:  startService 
 * --------------------
 * Start to run service on client
 * 
 *  clientSocket: self-explanatory
 *  user: if user is (1)root  or (0)non-root
 *
 */
void startService( int clientSocket, int user){
 

	// Auxiliar variables
	char buffer[MAXLINE];
	int i, aux;

	// Variable to store command select by client
	int command;
	bzero(buffer, MAXLINE);

	// loop to client iterate through commands
	do{

		gettingMenuFromServer(clientSocket);
		// Get action to be executed [1-8] and send to server
		fgets(buffer, MAXLINE, stdin);
		sendToServer(clientSocket, buffer);
		command = atoi(buffer);
		executeCommand(clientSocket, user, command);

	}while(1);

}

void main(){
	
	// Variable to store client socket
	int clientSocket;

	struct sockaddr_in serverAddr;
	
	int user;

	// socket create and verification
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(clientSocket<0){
		printf("[-] Fail to create the Socket\n");
		return;
	}
	printf("[+] Client Socket Created Sucessfully.\n");

	// assign IP, PORT
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	// Change here to the server host ip
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// connect the client socket to server socket
	if(connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))<0){
		perror("[-] Connection Error");
		// close(clientSocket);
		exit(EXIT_FAILURE);
	}
	printf("[+] Connected to Server.\n");

	// Login
	user = loginIntoServer(clientSocket);
	if(user >= 0){
		startService(clientSocket, user);
		
	}
	else{
		printf("[-] User not found.");
		printf("\n==============================================\n");
	}

}