


/*Number of items in menu*/
#define MAXSIZE 10
#define MAXLINE 1024

typedef struct _User {
	char *id;
	char *email;
	char *firstName;
	char *lastName;
	char *city;
	char *course;
	char *year;
    int nSkills;
	char **skills;
    int nExperiences;
	char **experiences;
    int root;
} User;



/*
 * Function:  lookForUser 
 * --------------------
 * look up user by email
 * 
 *  email: email to be search
 *  users: structure of users to look up
 *
 */
int lookForUser(char* email, User** users);


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
int addUser(char* email, char* firstName, char* lastName, char* city, \
			char* course, char* year, int nSkills, char** skills, \
			int nExperiences, char** experiences);

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
int addExperience(User* user, char* experience);

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
int removeUser(int id);

/*
 * Function:  getNumberOfUsers 
 * --------------------
 * count number of users registered 
 * 
 * returns:
 * 		- number of users registered  
 */
int getNumberOfUsers();

/*
 * Function:  initUser 
 * --------------------
 * initialization of user structure fields
 *  
 *  user : User structure 
 */
void initUser(User* user);

/*
 * Function:  initSkills 
 * --------------------
 * initialization of skill user structure fields
 *  
 *  user : User structure 
 */
void initSkills(User* user);

/*
 * Function:  initExperiences 
 * --------------------
 * initialization of experiences user structure fields
 *  
 *  user : User structure 
 */
void initExperiences(User* user);


/*
 * Function:  loadUserInfo 
 * --------------------
 * load info of the user
 *  
 *  user : User structure where the info will be stored
 *  fileName :  file path where the info is stored
 */
void loadUserInfo(User* user, char* fileName);

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
User** initUsers(int nUsers);

/*
 * Function:  loadUsers 
 * --------------------
 * load all users registred
 *  
 * returns: 
 *      users : array of User where all the users strutures are stored
 */
User** loadUsers();