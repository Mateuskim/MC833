


/*Number of items in menu*/
#define MAXSIZE 10
#define MAXCHAR 1000

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
Function : Adding new user
Arguments :
	- email: self-explained
	- firstName: self-explained
	- lastName: self-explained
	- city: self-explained
	- course: self-explained
	- year: self-explained
	- nSkills: Number of skills
	- skills: array of skills
	- nExperiences: Number of experiences
	- experiences: array of experiences
*/
int addUser(char* email, char* firstName, char* lastName, char* city, \
			char* course, char* year, int nSkills, char** skills, \
			int nExperiences, char** experiences);
int addUser1(char* email);

/*
Function : Adding new user
Arguments :
	- User to add experience
*/
int addExperience(User* user, char* experience);

/*
Function : Removing a existing user user
Arguments :
	- User to add experience
*/
int removeUser(int id);

/*
Function : Getting number of users registered in the platform
Arguments :
*/
int getNumberOfUsers();

/*
Function : Initializing user fields 
Arguments :
    - user: user struture
*/
void initUser(User* user);

/*
Function : Initializing skills fields 
Arguments :
    - user: user struture
*/
void initSkills(User* user);

/*
Function : Initializing experience fields 
Arguments :
    - user: user struture
*/
void initExperiences(User* user);


/*
Function : Loading infos of user from files in users
Arguments :
    - user: user struture
    - fileName: File name related to user
*/
void loadUserInfo(User* user, char* fileName);

/*
Function : Initializing user array
Arguments :
*/
User** initUsers(int nUsers);

/*
Function : Loading users into Server
Arguments :
*/
extern User** loadUsers();