#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

#define MAXCHAR 1000

int addUser(char* email, char* firstName, char* lastName, char* city,\
            char* course, char* year, int nSkills, char** skills,\
            int nExperiences, char** experiences){
    
    // Auxiliar variable
    int i;
    char fileName[MAXCHAR];
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
    fprintf(fp,"%s\n",email);
    fprintf(fp,"%s\n",firstName);
    fprintf(fp,"%s\n",lastName);
    fprintf(fp,"%s\n",city);
    fprintf(fp,"%s\n",course);
    fprintf(fp,"%s\n",year);
    fprintf(fp,"%d\n",nSkills);
    for (i = 0 ; i < nSkills; i++){
        fprintf(fp,"%s\n",skills[i]);
    }
    fprintf(fp,"%d\n",nExperiences);
    for (i = 0 ; i < nExperiences; i++){
        fprintf(fp,"%s\n",experiences[i]);
    }

    // Non root user
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
    char fileName[MAXCHAR];
    FILE *fp;

    // Variable to store new number of experiences
    int newNumberOfExperiences = user->nExperiences + 1;
    
    // Variable to store user's id
    int id = *(user->id) - '0';

    // Storing user file name into fileName variable
    snprintf(fileName, 27, "users/user%d.txt", id);
    fp = fopen(fileName, "w");

    // Rewriting user file with new experience
    fprintf(fp,"%d\n", id );
    fprintf(fp,"%s", user->email);
    fprintf(fp,"%s", user->firstName);
    fprintf(fp,"%s", user->lastName);
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
    fprintf(fp,"%s\n", experience);

    fprintf(fp,"%d\n", user->root);

    fclose(fp);
    return 1;
}

int removeUser(int id){
    // Auxiliar variable
    int numberOfUsers;
    char fileName[MAXCHAR];
    FILE *fp;
    int del;
    char str[MAXCHAR];

    // Getting the file name from user and store in fileName Variable
    snprintf(fileName, 27, "users/user%d.txt", id);
    del = remove(fileName);
    if (!del){
        printf("The file is Deleted successfully!\n");
        
        // Updating number of users
        fp = fopen("users/numberofusers.txt", "w+");
        if (fp == NULL){
            printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
            return 0;
        }

        fscanf(fp,"%d\n", &numberOfUsers);
        printf("number of users : %d\n", numberOfUsers);
        fprintf(fp,"%d\n",numberOfUsers-2);
        fclose(fp);
    }else{
        printf("the file was not Deleted!\n");
    }
    
}

int addUser1(char* email){
    int i;
    int n=getNumberOfUsers() + 1;
    char fileName[MAXCHAR];
    FILE *fp;
    

    printf("%d\n", n);
    snprintf(fileName, 27, "users/user%d.txt", n);

    fp = fopen(fileName, "w");

    fprintf(fp,"%s\n",email);
    
    fclose(fp);


    // Updating number of users
    fp = fopen("users/numberofusers.txt", "w");
    fprintf(fp,"%d\n",n);
    fclose(fp);


    return 0;
}


int getNumberOfUsers(){
    int numberOfFiles;
    char str[MAXCHAR];

    FILE *fp = fopen("users/numberofusers.txt", "rb");
    fgets(str, MAXCHAR, fp);

    numberOfFiles =  *str - '0';
    return numberOfFiles;
}

void initUser(User* user){
    user->id = malloc(MAXCHAR * sizeof(char));
    user->email = malloc(MAXCHAR * sizeof(char));
    user->firstName = malloc(MAXCHAR * sizeof(char));
    user->lastName = malloc(MAXCHAR * sizeof(char));
    user->city = malloc(MAXCHAR * sizeof(char));
    user->course = malloc(MAXCHAR * sizeof(char));
    user->year = malloc(MAXCHAR * sizeof(char));
}

void initSkills(User* user){
    int i ;
    user->skills = malloc(user->nSkills * sizeof(char*));
    for(i = 0; i < user->nSkills; i++){
        user->skills[i] = malloc(MAXCHAR * sizeof(char));
    }
}

void initExperiences(User* user){
    int i ;
    user->experiences = malloc(user->nExperiences * sizeof(char*));
    for(i = 0; i < user->nExperiences; i++){
        user->experiences[i] = malloc(MAXCHAR * sizeof(char));
    }
}

void loadUserInfo(User* user, char* fileName){
    char str[MAXCHAR];
    int nSkills;
    int nExperiences;
    int i ;
    FILE *fp = fopen(fileName, "rb");

    if (fp == NULL){
        printf("Could not open user file");
        return;
    }
    // id
    fgets(str, MAXCHAR, fp);
    strcpy(user->id, str);

    // email
    fgets(str, MAXCHAR, fp);
    strcpy(user->email, str);

    // first name
    fgets(str, MAXCHAR, fp);
    strcpy(user->firstName, str);

    // last name
    fgets(str, MAXCHAR, fp);
    strcpy(user->lastName, str);

    // city
    fgets(str, MAXCHAR, fp);
    strcpy(user->city, str);

    // course
    fgets(str, MAXCHAR, fp);
    strcpy(user->course, str);

    // year
    fgets(str, MAXCHAR, fp);
    strcpy(user->year, str);

    // skills
    fgets(str, MAXCHAR, fp);
    user->nSkills = *str - '0';
    initSkills(user);

    // Iterating through user skills
    for(i = 0 ; i < user->nSkills; i++){
        fgets(str, MAXCHAR, fp);
        strcpy(user->skills[i], str);
    }


    // experiences
    fgets(str, MAXCHAR, fp);
    user->nExperiences = *str - '0'; 
    initExperiences(user);

    // Iterating through user experiences
    for(i = 0 ; i < user->nExperiences; i++){
        fgets(str, MAXCHAR, fp);
        strcpy(user->experiences[i], str);
    }

    // root
    fgets(str, MAXCHAR, fp);
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
    char fileName[MAXCHAR];
    int i, nUsers = getNumberOfUsers();
    User** users;

    users = initUsers(nUsers);

    for(i = 1 ; i <= nUsers ; i++){

    //     // Getting user i name file  
        snprintf(fileName, 16, "users/user%d.txt", i);
        loadUserInfo(users[i-1], fileName);
    }
    return users;
}
