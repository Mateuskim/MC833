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
#define ROOTMENUSIZE "8"
#define USERMENUSIZE "5"

int lookForUser(char* email, User** users){

    // Auxiliar variable
    int i;
    printf("========= lookgin for user =============\n\n");
    // Variable to store number of users registered
    int numberOfUsers = getNumberOfUsers();
    // Looking for user
    for (i = 0 ; i < numberOfUsers ; i++){
        if(strcmp(users[i]->email, email) == 0){
            return users[i]->root;
        }
    }

    printf("\n=====================================\n\n");
    // If there is no user with that email
    return -1;
}

int login(int connfd){

    // Auxiliar variable
    char buffer[MAXLINE];

    // Variable to store users registered
    User** users = loadUsers();

    // Variable to store email to login
    char email[MAXLINE];

    // Getting email from client
    if (recv(connfd, buffer, MAXLINE,0) == 0){
        //error: server terminated prematurely
        perror("Server terminated prematurely");
        exit(0);
    }
    strcpy(email, buffer);
    printf("\n----\nemail: %s\n----\n", buffer);


    return lookForUser(email, users);
    
}
void sendMenuToClient(int connfd, int user){

    // Auxiliar variables
    int i;
    char menuItem[MAXLINE];
    FILE *fp ;

    // Variable to store size of menu as int
    int menuSize;

    if(user == 1){
        menuSize = atoi(ROOTMENUSIZE);
        fp = fopen("menu/menuRoot.txt", "r");
         // Sending menu size to client
        send(connfd, ROOTMENUSIZE, MAXLINE, 0);
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

void startService( int connfd, int user_login){
    ssize_t n;
    char buffer[MAXLINE];
    char *email;
    int i;

    if(user_login == 1){
        printf("[+] Root has logged in!\n");
    }else{
        printf("[+] An user has logged in!\n");
    }

    sendMenuToClient(connfd, user_login);
   

    while(1){
       if (recv(connfd, buffer, MAXLINE,0) == 0){
            //error: server terminated prematurely
            perror("[-] The server terminated prematurely");
            exit(0);
        }

        send(connfd, "Item received Sucessfully\n", MAXLINE, 0);
    }
}

int main(){


    // removeUser(4);
    // addUser1("mateuskimura@gmail.com");
    int connfd = 0;
    char request[100];
    char *fname;
    pid_t pid;

    int user_login;

    struct sockaddr_in address;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    address.sin_family = AF_INET;

    int address_len = sizeof(address);

    // socket()
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0){
        printf("[-] Socket creation error!\n");
        return 1;
    }else{
        printf("[+] Socket creation success!\n");
    }

    // bind()
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
        printf("Waiting ...\n");
        
		// accept()
        connfd = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&address_len);
        if (connfd < 0){
            printf("[-] Error in accept!\n");
            continue;
        }
        printf("New connection established\n");

        if ( (pid = fork()) == 0 ) {
           
            close(listening); /* child closes listening socket */

            user_login = login(connfd);

            if(user_login >= 0){
                // User Found!
                send(connfd, "1", MAXLINE, 0);
                
                startService(connfd, user_login);
            }

            /***process the request doing something using connfd ***/
            /* ................. */

            close(connfd);
            exit(0); //child terminates
        }

       
    }

    return 0;
}