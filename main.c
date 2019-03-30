#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "user_registration.h"

int main()
{
    //Initializing the file
    FILE *file = fopen("users.txt","w+b");
    if(file == NULL){
        printf("Error in the file creation.");
        system("pause");
        exit(0);
    }
    fclose(file);

    bool leave = false;
    int users = 0;

    while(!leave)menu(&leave,file,&users);

    return 0;
}
