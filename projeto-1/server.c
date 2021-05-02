#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"

#define PORT 8080
#define MAXLINE 1024
#define MAX 10
#define ROOTMENUSIZE "9"
#define USERMENUSIZE "6"


/*
 * Function:  receiveFromClient 
 * --------------------
 * Receives a message from client and stores on the buffer
 * 
 *  connfd: client socket connection
 *  buffer: stores the incoming message
 *
 */
void receiveFromClient(int connfd, char* buffer){
     // Getting email from client
    if (recv(connfd, buffer, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("Server terminated prematurely");
        exit(0);
    }
}

/*
 * Function:  sendMessageToClient 
 * --------------------
 * Send a message to client
 * 
 *  connfd: client socket connection
 *  msg: message to send
 *
 */
void sendMessageToClient(int connfd, char msg[MAXLINE]){
    send(connfd, msg, MAXLINE, 0);
}

/*
 * Function:  sendIntToClient 
 * --------------------
 * Send a int as a message to client
 * 
 *  connfd: client socket connection
 *  n: integer to send
 *
 */
void sendIntToClient(int connfd, int n){
    char buffer[MAXLINE];
    snprintf(buffer, MAXLINE, "%d", n);
    sendMessageToClient(connfd, buffer);
}


/*
 * Function:  lookForUser 
 * --------------------
 * look up user by email
 * 
 *  email: email to be search
 *  users: structure of users to look up
 *
 */
int lookForUser(char* email, User** users){

    // Auxiliar variable
    int i;
    // Variable to store number of users registered
    int numberOfUsers = getNumberOfUsers();
    // Looking for user
    for (i = 0 ; i < numberOfUsers ; i++){
        if(strcmp(users[i]->email, email) == 0){
            return users[i]->root;
        }
    }

    // If there is no user with that email
    return -1;
}

/*
 * Function:  login 
 * --------------------
 * get email from client and look up the email on the database
 * 
 *  connfd: client socket connection
 *
 */
int login(int connfd){

    // Auxiliar variable
    char buffer[MAXLINE];

    // Variable to store users registered
    User** users = loadUsers();

    // Variable to store email to login
    char email[MAXLINE];

    // Getting email from client
    receiveFromClient(connfd, buffer);

    return lookForUser(buffer, users);
    
}

/*
 * Function:  sendMenuToClient 
 * --------------------
 * get the right menu (root/non-root) and send to client
 * 
 *  connfd: client socket connection
 *  user: 1 if user root - 0 if not
 *
 */
void sendMenuToClient(int connfd, int user){

    // Auxiliar variables
    int i;
    char menuItem[MAXLINE];
    FILE *fp ;

    // Variable to store size of menu as int
    int menuSize;

    // If it is the root user
    if(user == 1){
        menuSize = atoi(ROOTMENUSIZE);
        fp = fopen("menu/menuRoot.txt", "r");
         // Sending menu size to client
        send(connfd, ROOTMENUSIZE, MAXLINE, 0);

    // If it is a normal user
    }else{
        menuSize = atoi(USERMENUSIZE);
        fp = fopen("menu/menuUser.txt", "r");
        send(connfd, USERMENUSIZE, MAXLINE, 0);
    }
    
    // Sending items of menu store in menu/menu.txt
    while (fgets(menuItem, MAXCHAR, fp) != NULL)
        send(connfd, menuItem, MAXLINE, 0);
    fclose(fp);
    
}

/*
 * Function:  listUsersByCourse 
 * --------------------
 * get list of users by course and send it to client
 * 
 *  connfd: client socket connection
 *
 */
void listUsersByCourse(int connfd){

    int i;
    char buffer[MAXLINE],  course[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;
    
    // Receiving course
    receiveFromClient(connfd, buffer);
    
    strcpy(course, buffer);
    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->course, course) == 0)
            usersFound += 1;
    }
    sendIntToClient(connfd, usersFound);
    if(usersFound)
        for(i = 0; i < numberOfUsers; i++)
            if(strcmp(users[i]->course, course) == 0){
                snprintf(buffer, MAXLINE, "\n--User %d--\nEmail: %s",i+1, \
                                                            users[i]->email);
                sendMessageToClient(connfd, buffer);
                snprintf(buffer, MAXLINE, "Name: %s %s\n", users[i]->firstName, \
                                                        users[i]->lastName);
                sendMessageToClient(connfd, buffer);
            }
}

/*
 * Function:  listUsersByYear 
 * --------------------
 * get list of users by graduation year and send it to client
 * 
 *  connfd: client socket connection
 *
 */
void listUsersByYear(int connfd){

    int i;
    char buffer[MAXLINE],  year[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;

    receiveFromClient(connfd, buffer);

    strcpy(year, buffer);
    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->year, year) == 0)
            usersFound += 1;
    }
    sendIntToClient(connfd, usersFound);
    if(usersFound)
        for(i = 0; i < numberOfUsers; i++)
            if(strcmp(users[i]->year, year) == 0){
                snprintf(buffer, MAXLINE, "\n--User %d--\nEmail: %s",i+1, \
                                                            users[i]->email);
                sendMessageToClient(connfd, buffer);
                snprintf(buffer, MAXLINE, "Name: %s %s\n", users[i]->firstName, \
                                                        users[i]->lastName);
                sendMessageToClient(connfd, buffer);
            }
}

/*
 * Function:  toUpperCase 
 * --------------------
 * uppercase str
 * 
 *  str: string to uppercase
 *
 */
void toUpperCase(char *str){
    while(*str) 
    {
        *str = (*str >= 'a' && *str <= 'z') ? *str-32 : *str;
        str++;
    }
}

/*
 * Function:  listUsersBySkill 
 * --------------------
 * get list of users by skill and send it to client
 * 
 *  connfd: client socket connection
 *
 */
void listUsersBySkill(int connfd){

    int i, j;

    char buffer[MAXLINE], skill[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;

    // Receiving skill
    receiveFromClient(connfd, buffer);

    strcpy(skill, buffer);

     // upper skill typed
    toUpperCase(skill);
    for(i = 0; i < numberOfUsers; i++){
        for(j = 0 ; j < users[i]->nSkills; j++){
            
            // upper user skill stored 
            toUpperCase(users[i]->skills[j]);

            if(strstr(users[i]->skills[j], skill) != NULL){
                usersFound += 1;
                printf("%s %s\n\n", users[i]->skills[j], skill);

                break;
            }
                
        }
        
    }
    sendIntToClient(connfd, usersFound);
    if(usersFound)
        for(i = 0; i < numberOfUsers; i++){

            // upper skill typed
            
            for(j = 0 ; j < users[i]->nSkills; j++){

                if(strstr(users[i]->skills[j], skill)!=NULL){
                    snprintf(buffer, MAXLINE, "\n--User %d--\nEmail: %s",i+1, \
                                                                users[i]->email);
                    sendMessageToClient(connfd, buffer);
                    snprintf(buffer, MAXLINE, "Name: %s %s", users[i]->firstName, \
                                                        users[i]->lastName);
                    sendMessageToClient(connfd, buffer);
                    snprintf(buffer, MAXLINE, "Skill: %s", users[i]->skills[j]);
                    sendMessageToClient(connfd, buffer);
                    // leaves loop
                    j = users[i]->nSkills;

                 }

            }
        }
}

/*
 * Function:  listUsers 
 * --------------------
 * get list of all users send it to client
 * 
 *  connfd: client socket connection
 *
 */
void listUsers(int connfd){

    int i;
    char buffer[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();


    sendIntToClient(connfd, numberOfUsers);
    if(numberOfUsers)
        for(i = 0; i < numberOfUsers; i++){
            snprintf(buffer, MAXLINE, "\n--User %d--\nEmail: %s",i+1, \
                                                        users[i]->email);
            sendMessageToClient(connfd, buffer);
            snprintf(buffer, MAXLINE, "Name: %s %s\n", users[i]->firstName, \
                                                        users[i]->lastName);
            sendMessageToClient(connfd, buffer);
        }

}

/*
 * Function:  listUserByEmail 
 * --------------------
 * search user by email and send to client
 * 
 *  connfd: client socket connection
 *
 */
void listUserByEmail(int connfd){

    int i, j;
    char buffer[MAXLINE], email[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;

    // Receiving email
    receiveFromClient(connfd, buffer);
    strcpy(email, buffer);
    

    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->email, email) == 0)
            usersFound += 1;
    }
    sendIntToClient(connfd, usersFound);
    for(i = 0; i < numberOfUsers; i++)
        if(strcmp(users[i]->email, email) == 0){
            
            // Sending email
            snprintf(buffer, MAXLINE, "\n--User %d--\nEmail: %s",i+1, \
                                                        users[i]->email);
            sendMessageToClient(connfd, buffer);

            // Sending name
            snprintf(buffer, MAXLINE, "Name: %s %s", users[i]->firstName, \
                                                     users[i]->lastName);
            sendMessageToClient(connfd, buffer);

            // Sending city
            snprintf(buffer, MAXLINE, "City: %s", users[i]->city);
            sendMessageToClient(connfd, buffer);

            // Sending course
            snprintf(buffer, MAXLINE, "Course: %s", users[i]->course);
            sendMessageToClient(connfd, buffer);
            
            // Sending year of graduation
            snprintf(buffer, MAXLINE, "Graduation year: %s", users[i]->year);
            sendMessageToClient(connfd, buffer);


            // Sending number of skills
            snprintf(buffer, MAXLINE, "%d", users[i]->nSkills);
            sendMessageToClient(connfd, buffer);

            // Sending skills
            for(j = 0 ; j < users[i]->nSkills; j++){
                snprintf(buffer, MAXLINE, "Skill %d: %s",j+1, users[i]->skills[j]);
                sendMessageToClient(connfd, buffer);
            }

            // Sending number of experiences
            snprintf(buffer, MAXLINE, "%d", users[i]->nExperiences);
            sendMessageToClient(connfd, buffer);
            
            // Sending experiences
            for(j = 0 ; j < users[i]->nExperiences; j++){
                snprintf(buffer, MAXLINE, "Experience %d: %s",j+1, users[i]->experiences[j]);
                sendMessageToClient(connfd, buffer);
            }

        }
}

/*
 * Function:  removeUserByEmail 
 * --------------------
 * remove user 
 * 
 *  connfd: client socket connection
 *
 */
void removeUserByEmail(int connfd){

    int i, j;
    char buffer[MAXLINE], email[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;

    
    // Receiving email from client
    receiveFromClient(connfd, buffer);
    strcpy(email, buffer);

    // go through users to check number of users found
    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->email, email) == 0)
            usersFound += 1;
    }
    // send number of users found before send users
    sendIntToClient(connfd, usersFound);

    if(usersFound){
        // go through users to send to client
        for(i = 0; i < numberOfUsers; i++)
            if(strcmp(users[i]->email, email) == 0){
                if(removeUser(atoi(users[i]->id))){
                    sendMessageToClient(connfd, "User Deleted\n");
                    return;
                }
            }
        
        sendMessageToClient(connfd, "[ERROR] User not Deleted\n");
    }
}
        

/*
 * Function:  addExperienceUser 
 * --------------------
 * add new experience to user
 * 
 *  connfd: client socket connection
 *
 */
void addExperienceUser(int connfd){

    int i, j;
    char buffer[MAXLINE], email[MAXLINE];
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();
    int usersFound = 0;

    receiveFromClient(connfd, buffer);
    strcpy(email, buffer);


    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->email, email) == 0)
            usersFound += 1;
    }
    sendIntToClient(connfd, usersFound);

    if(usersFound){
        for(i = 0; i < numberOfUsers; i++)
            if(strcmp(users[i]->email, email) == 0){
                // reading skill
                receiveFromClient(connfd, buffer);
                if(addExperience(users[i], buffer)){
                    sendMessageToClient(connfd,"Skill added succesfully\n");
                    return;
                }
            }
        send(connfd, "Skill add gone wrong\n", MAXLINE, 0);
    }
    
}

/*
 * Function:  addNewUser 
 * --------------------
 * add new user to database
 * 
 *  connfd: client socket connection
 *
 */
void addNewUser(int connfd){

    // Variables to store existent users info
    User** users = loadUsers();
    int numberOfUsers = getNumberOfUsers();

    // Variables to store new user info
    char email[MAXLINE], firstName[MAXLINE], lastName[MAXLINE], city[MAXLINE] \
        , course[MAXLINE], year[MAXLINE];
    char **skills, **experiences; 
    int nSkills, nExperiences;
    
    // Auxiliar variables
    int i, j;
    char buffer[MAXLINE], user_created=0;


    // Initial values set to enter in loop
    int flag_continue=1,usersFound = 0;
    receiveFromClient(connfd, buffer);
    sendMessageToClient(connfd, "Checking if email already exists.");
    strcpy(email, buffer);

    // search user
    for(i = 0; i < numberOfUsers; i++){
        if(strcmp(users[i]->email, email) == 0){
            usersFound += 1;
        }
            
    }
    sendIntToClient(connfd, usersFound);
    if(!usersFound){

        // First Name
        receiveFromClient(connfd, buffer);
        strcpy(firstName, buffer);
        
        // Last Name
        receiveFromClient(connfd, buffer);
        strcpy(lastName, buffer);
        
        // City
        receiveFromClient(connfd, buffer);
        strcpy(city, buffer);
        
        // Course
        receiveFromClient(connfd, buffer);
        strcpy(course, buffer);
        
        // Graduation year
        receiveFromClient(connfd, buffer);
        strcpy(year, buffer);
        
        // Number of Skills
        receiveFromClient(connfd, buffer);
        nSkills = atoi(buffer);
        skills = malloc(nSkills);
        for(i = 0 ; i < nSkills; i++){
            skills[i] = malloc(MAXLINE * sizeof(char));
        }

        for(i = 0 ; i < nSkills; i++){
            receiveFromClient(connfd, buffer);
            strcpy(skills[i], buffer);
        }

         // Number of Experience
        receiveFromClient(connfd, buffer);
        nExperiences = atoi(buffer);

        experiences = malloc(nExperiences);
        for(i = 0 ; i < nExperiences; i++){
            experiences[i] = malloc(MAXLINE * sizeof(char));
        }

        for(i = 0 ; i < nExperiences; i++){
            receiveFromClient(connfd, buffer);
            strcpy(experiences[i], buffer);
        }

        // Adding new user
        user_created = addUser(email, firstName, lastName, city, course \
                ,year, nSkills, skills, nExperiences, experiences);
        sendIntToClient(connfd, user_created);
    }
}


/*
 * Function:  executeCommand 
 * --------------------
 * map the commands of the user and executes
 * 
 *  connfd: client socket connection
 *  user: 1 if root - 0 if non root
 *  command: command to be executed
 *
 */
void executeCommand(int connfd, int user, int command){

    // Root User
    if(user == 1){
        switch(command){
            case 1:
                printf("[+] Root adding new User\n");
                addNewUser(connfd);
            break;
            case 2:
                printf("[+] Root adding skill\n");
                addExperienceUser(connfd);
            break;
            case 3:
                printf("[+] Root listing by couse\n");
                listUsersByCourse(connfd);
            break;
            case 4:
                printf("[+] Root listing by Skill\n");
                listUsersBySkill(connfd);
            break;
            case 5:
                printf("[+] Root listing by year\n");
                listUsersByYear(connfd);
            break;
            case 6:
                printf("[+] Root listing all users\n");
                listUsers(connfd);
            break;
            case 7:
                printf("[+] Root searching user\n");
                listUserByEmail(connfd);
            break;
            case 8:
                printf("[+] Root deleting user\n");
                removeUserByEmail(connfd);
            break;
            case 9:
				exit(0);
            break;
        }

        
    // Non root user
    }else{
        switch(command){
            case 1:
                printf("[+] User listing by couse\n");
                listUsersByCourse(connfd);
            break;
            case 2:
                printf("[+] User listing by skill\n");
                listUsersBySkill(connfd);
            break;
            case 3:
                printf("[+] User listing by year\n");
                listUsersByYear(connfd);
            break;
            case 4:
                printf("[+] User listing all users\n");
                listUsers(connfd);
            break;
            case 5:
                printf("[+] User searching user\n");
                listUserByEmail(connfd);
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
 * send the menu to client and receives each menu.
 * 
 *  connfd: client socket connection
 *  user: 1 if root - 0 if non root
 *
 */
void startService( int connfd, int user){
    ssize_t n;
    char buffer[MAXLINE];
    char *email;
    int i, command;

    if(user == 1){
        printf("[+] Root has logged in!\n");
    }else{
        printf("[+] An user has logged in!\n");
    }

    do{
        sendMenuToClient(connfd, user);
        // Receiving action to be executed
        if (recv(connfd, buffer, MAXLINE,0) == 0){
            //error: server terminated prematurely
            perror("[-] The server terminated prematurely");
            exit(0);
        }
        command = atoi(buffer);
        executeCommand(connfd, user, command);
    }while(1);
}

int main(){
    int connfd = 0;
    pid_t pid;

    int user_login;

    struct sockaddr_in address;
    // assign IP, PORT
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    address.sin_family = AF_INET;

    int address_len = sizeof(address);

    // socket create and verification
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0){
        printf("[-] Socket creation error!\n");
        return 1;
    }else{
        printf("[+] Socket creation success!\n");
    }

    // bind
    int server_bind = bind(sockfd, (struct sockaddr *)&address, sizeof(address));
    if (server_bind) {
        printf("[-] Server binding failed!\n");
        return 1;
    }else{
        printf("[+] Server binding success!\n");
    }

    // listen()
    int listening = listen(sockfd, 5);
    if (listening < 0){
        printf("[-] Failed to listen!\n");
        return 1;
    }

    while (1){
        printf("Waiting for connection...\n");
        
		// accept()
        connfd = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&address_len);
        if (connfd < 0){
            printf("[-] Error in accept!\n");
            continue;
        }
        printf("[+] New connection established\n");

        // copy process and execute the parent
        if ( (pid = fork()) == 0 ) {
           
            close(listening); /* child closes listening socket */

            user_login = login(connfd);

            if(user_login >= 0){
                // User Found!
                send(connfd, "1", MAXLINE, 0);
                
                startService(connfd, user_login);
            }else{
                send(connfd, "-1", MAXLINE, 0);
            }

            close(connfd);
            exit(0); //child terminates
        }

       
    }

    return 0;
}