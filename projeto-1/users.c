#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

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

int addUser(char* email, char* firstName, char* lastName, char* city,\
            char* course, char* year, int nSkills, char** skills,\
            int nExperiences, char** experiences){
    
    // Auxiliar variable
    int i;
    char fileName[MAXLINE];
    FILE *fp;

    // Variable to store number of users registered
    int id =getNumberOfUsers() + 1;

    // Storing user file name into fileName variable
    snprintf(fileName, 27, "users/user%d.txt", id);

    // Creating and writing users
    fp = fopen(fileName, "w");
    if (fp == NULL){
        printf("[-] Could not create user !!");
        return 0;
    }

    // Writing user file with given infos
    printf("[+] Adding user number %d ...\n", id);
    fprintf(fp,"%d\n",id);
    fprintf(fp,"%s",email);
    fprintf(fp,"%s",firstName);
    fprintf(fp,"%s",lastName);
    fprintf(fp,"%s",city);
    fprintf(fp,"%s",course);
    fprintf(fp,"%s",year);
    fprintf(fp,"%d\n",nSkills);

    // loop to write skills on the user's file
    for (i = 0 ; i < nSkills; i++){
        fprintf(fp,"%s",skills[i]);
    }
    fprintf(fp,"%d\n",nExperiences);
    
    // loop to write experiences on the user's file

    for (i = 0 ; i < nExperiences; i++){
        fprintf(fp,"%s",experiences[i]);
    }

    // Non root user - every user added will be non-root
    fprintf(fp,"%d\n",0);

    fclose(fp);


    // Updating number of users
    fp = fopen("users/numberofusers.txt", "w");
    fprintf(fp,"%d\n",id);
    fclose(fp);

    return 1;
}

int addExperience(User* user, char* experience){

    // Auxiliar variable
    int i;
    char fileName[MAXLINE];
    FILE *fp;

    // Variable to store new number of experiences
    int newNumberOfExperiences = user->nExperiences + 1;
    
    // Variable to store user's id
    int id = *(user->id) - '0';

    // Storing user file name into fileName variable
    snprintf(fileName, 27, "users/user%d.txt", id);
    fp = fopen(fileName, "w");
    if (fp == NULL){
        printf("[-] Could not add experience !!");
        return 0;
    }

    // Rewriting user file with new experience
    fprintf(fp,"%d\n", id );
    fprintf(fp,"%s", user->email);
    fprintf(fp,"%s\n", user->firstName);
    fprintf(fp,"%s\n", user->lastName);
    fprintf(fp,"%s", user->city);
    fprintf(fp,"%s", user->course);
    fprintf(fp,"%s", user->year);
    fprintf(fp,"%d\n", user->nSkills);
    for (i = 0 ; i < user->nSkills; i++){
        fprintf(fp,"%s", user->skills[i]);
    }

    // New number of experiences
    fprintf(fp,"%d\n", user->nExperiences + 1);

    // Past experiences
    for (i = 0 ; i < user->nExperiences; i++){
        fprintf(fp,"%s", user->experiences[i]);
    }

    // Adding new experience
    fprintf(fp,"%s", experience);

    fprintf(fp,"%d\n", user->root);

    fclose(fp);
    return 1;
}

int removeUser(int id){

    // Auxiliar variable
    int numberOfUsers;
    char fileName[MAXLINE];
    FILE *fp;

    // variable to store result of file removed.
    int del;

    // Getting the file name from user and store in fileName Variable
    snprintf(fileName, 27, "users/user%d.txt", id);
    del = remove(fileName);

    // if remove runs successfully
    if (!del){
        printf("The file is Deleted successfully!\n");
        
        // Updating number of users
        fp = fopen("users/numberofusers.txt", "w+");
        if (fp == NULL){
            printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
            return 0;
        }

        // writing new number of users
        fscanf(fp,"%d\n", &numberOfUsers);
        printf("number of users : %d\n", numberOfUsers-2);
        fprintf(fp,"%d\n",numberOfUsers-2);
        fclose(fp);
        return 1;
    }else{
        printf("the file was not Deleted!\n");
        return 0;
    }
    
}

int getNumberOfUsers(){
    int numberOfFiles;
    char str[MAXLINE];

    FILE *fp = fopen("users/numberofusers.txt", "rb");
    fgets(str, MAXLINE, fp);

    numberOfFiles =  *str - '0';
    return numberOfFiles;
}


void initUser(User* user){
    user->id = malloc(MAXLINE * sizeof(char));
    user->email = malloc(MAXLINE * sizeof(char));
    user->firstName = malloc(MAXLINE * sizeof(char));
    user->lastName = malloc(MAXLINE * sizeof(char));
    user->city = malloc(MAXLINE * sizeof(char));
    user->course = malloc(MAXLINE * sizeof(char));
    user->year = malloc(MAXLINE * sizeof(char));
}

void initSkills(User* user){
    int i ;
    user->skills = malloc(user->nSkills * sizeof(char*));
    for(i = 0; i < user->nSkills; i++){
        user->skills[i] = malloc(MAXLINE * sizeof(char));
    }
}

void initExperiences(User* user){
    int i ;
    user->experiences = malloc(user->nExperiences * sizeof(char*));
    for(i = 0; i < user->nExperiences; i++){
        user->experiences[i] = malloc(MAXLINE * sizeof(char));
    }
}

void loadUserInfo(User* user, char* fileName){
    char str[MAXLINE];
    int nSkills, nExperiences;
    int i ;

    // Variable to store the file
    FILE *fp = fopen(fileName, "rb");

    if (fp == NULL){
        printf("Could not open user file");
        return;
    }
    // id
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->id, str);

    // email
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->email, str);

    // first name
    fscanf(fp, "%s\n", str);
    strcpy(user->firstName, str);

    // last name
    fscanf(fp, "%s\n", str);
    strcpy(user->lastName, str);

    // city
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->city, str);

    // course
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->course, str);

    // year
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->year, str);

    // skills
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    user->nSkills = *str - '0';
    initSkills(user);

    // Iterating through user skills
    for(i = 0 ; i < user->nSkills; i++){
        fgets(str, MAXLINE, fp);
        str[strcspn(str, "\n")] = 0;
        strcpy(user->skills[i], str);
    }

    // experiences
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    user->nExperiences = *str - '0'; 
    initExperiences(user);

    // Iterating through user experiences
    for(i = 0 ; i < user->nExperiences; i++){
        fgets(str, MAXLINE, fp);
        str[strcspn(str, "\n")] = 0;
        strcpy(user->experiences[i], str);
    }

    // root
    fgets(str, MAXLINE, fp);
    str[strcspn(str, "\n")] = 0;
    user->root = *str - '0';

    fclose(fp);

}

User** initUsers(int nUsers){
    int i;
    User** users = malloc(nUsers * sizeof(User*));

    for(i = 0 ; i < nUsers; i++){
        users[i] = malloc(sizeof(User));
        initUser(users[i]);
    }
    return users;
}

User** loadUsers(){

    // Variable to store the file name path
    char fileName[MAXLINE];
    int i, nUsers = getNumberOfUsers();
    User** users;

    users = initUsers(nUsers);

    for(i = 1 ; i <= nUsers ; i++){

        // Getting user i name file  and stores on fileName variable
        snprintf(fileName, 16, "users/user%d.txt", i);
        loadUserInfo(users[i-1], fileName);
    }
    return users;
}
