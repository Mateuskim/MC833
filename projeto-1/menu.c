#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Number of items in menu*/
#define SIZE 8
#define MAXCHAR 33

#define MAXLINE 1024

const char *tmp = "This string literal is arbitrary";

void toUpperCase(char *str){
    while(*str) 
    {
        *str = (*str >= 'a' && *str <= 'z') ? *str-32 : *str;
        str++;
    }
}

int main(){
    char *ret;
    	// Auxiliar variable
	char buffer[MAXLINE];
    int l = 0;

	fgets(buffer, MAXLINE, stdin);
    buffer[strlen(buffer)-1] = '\0';
    printf("\nstring =%s--\n", buffer);

    ret = strstr(tmp, buffer);
    if (ret)
        printf("found substring at address %p\n", ret);
    else
        printf("no substring found!\n");

    exit(EXIT_SUCCESS);

}