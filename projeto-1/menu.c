#include <stdio.h>
#include <stdlib.h>

/*Number of items in menu*/
#define SIZE 8
#define MAXCHAR 33


int main(){
    // char menu[SIZE * MAXCHAR];
    char str[MAXCHAR];

    /*Opening file*/
	FILE *fp = fopen("menu/menu.txt", "rb");

    if (fp == NULL){
        printf("Could not open menu file");
        return 1;
    }

    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str); // change to write in server.c
    fclose(fp);
    return 1;
}