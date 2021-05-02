#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

/*
 * Function:  addUser 
 * --------------------
 * add new user into the database
 * 
 * arguments:
 *  email: self-explanatory
 *  firstName: self-explanatory
 *  lastName: self-explanatory
 *  city: self-explanatory
 *  course: self-explanatory
 *  year: self-explanatory
 *  nSkills: number of skills of the user
 *  skills: array of string with skills of the user
 *  nExperiences: number of experience of the user
 *  experiences: array of experiences with skills of the user
 *
 */
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

/*
 * Function:  addExperience 
 * --------------------
 * add new experience to user
 * 
 *  user: usert structure to where new experience will be added
 *  experience: experience to be added
 *  
 * returns:
 * 		0 - if add experience failed
 * 		1 - if experience added successfully
 */
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

/*
 * Function:  removeUser 
 * --------------------
 * remove user from the database
 * 
 *  id: id of the file where the user has been stored
 *  
 * returns:
 * 		0 -  user remove failed
 * 		1 - if user removed successfully
 */

int removeUser(int id){

    // Auxiliar variable
    int numberOfUsers;
    char fileName[MAXCHAR];
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

/*
 * Function:  getNumberOfUsers 
 * --------------------
 * count number of users registered 
 * 
 * returns:
 * 		- number of users registered  
 */
int getNumberOfUsers(){
    int numberOfFiles;
    char str[MAXCHAR];

    FILE *fp = fopen("users/numberofusers.txt", "rb");
    fgets(str, MAXCHAR, fp);

    numberOfFiles =  *str - '0';
    return numberOfFiles;
}


/*
 * Function:  initUser 
 * --------------------
 * initialization of user structure fields
 *  
 *  user : User structure 
 */
void initUser(User* user){
    user->id = malloc(MAXCHAR * sizeof(char));
    user->email = malloc(MAXCHAR * sizeof(char));
    user->firstName = malloc(MAXCHAR * sizeof(char));
    user->lastName = malloc(MAXCHAR * sizeof(char));
    user->city = malloc(MAXCHAR * sizeof(char));
    user->course = malloc(MAXCHAR * sizeof(char));
    user->year = malloc(MAXCHAR * sizeof(char));
}

/*
 * Function:  initSkills 
 * --------------------
 * initialization of skill user structure fields
 *  
 *  user : User structure 
 */
void initSkills(User* user){
    int i ;
    user->skills = malloc(user->nSkills * sizeof(char*));
    for(i = 0; i < user->nSkills; i++){
        user->skills[i] = malloc(MAXCHAR * sizeof(char));
    }
}

/*
 * Function:  initExperiences 
 * --------------------
 * initialization of experiences user structure fields
 *  
 *  user : User structure 
 */
void initExperiences(User* user){
    int i ;
    user->experiences = malloc(user->nExperiences * sizeof(char*));
    for(i = 0; i < user->nExperiences; i++){
        user->experiences[i] = malloc(MAXCHAR * sizeof(char));
    }
}

/*
 * Function:  loadUserInfo 
 * --------------------
 * load info of the user
 *  
 *  user : User structure where the info will be stored
 *  fileName :  file path where the info is stored
 */
void loadUserInfo(User* user, char* fileName){
    char str[MAXCHAR];
    int nSkills, nExperiences;
    int i ;

    // Variable to store the file
    FILE *fp = fopen(fileName, "rb");

    if (fp == NULL){
        printf("Could not open user file");
        return;
    }
    // id
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->id, str);

    // email
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->email, str);

    // first name
    fscanf(fp, "%s\n", str);
    strcpy(user->firstName, str);

    // last name
    fscanf(fp, "%s\n", str);
    strcpy(user->lastName, str);

    // city
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->city, str);

    // course
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->course, str);

    // year
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    strcpy(user->year, str);

    // skills
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    user->nSkills = *str - '0';
    initSkills(user);

    // Iterating through user skills
    for(i = 0 ; i < user->nSkills; i++){
        fgets(str, MAXCHAR, fp);
        str[strcspn(str, "\n")] = 0;
        strcpy(user->skills[i], str);
    }


    // experiences
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    user->nExperiences = *str - '0'; 
    initExperiences(user);

    // Iterating through user experiences
    for(i = 0 ; i < user->nExperiences; i++){
        fgets(str, MAXCHAR, fp);
        str[strcspn(str, "\n")] = 0;
        strcpy(user->experiences[i], str);
    }

    // root
    fgets(str, MAXCHAR, fp);
    str[strcspn(str, "\n")] = 0;
    user->root = *str - '0';

    fclose(fp);

}

/*
 * Function:  initUsers 
 * --------------------
 * init array of users structures 
 *  
 *  nUsers : number of users to initiazate
 * 
 *  returns:
 *        users:  an user structure where the fields are initialized
 */
User** initUsers(int nUsers){
    int i;
    User** users = malloc(nUsers * sizeof(User*));

    for(i = 0 ; i < nUsers; i++){
        users[i] = malloc(sizeof(User));
        initUser(users[i]);
    }
    return users;
}

/*
 * Function:  loadUsers 
 * --------------------
 * load all users registred
 *  
 * returns: 
 *      users : array of User where all the users strutures are stored
 */
User** loadUsers(){

    // Variable to store the file name path
    char fileName[MAXCHAR];
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
