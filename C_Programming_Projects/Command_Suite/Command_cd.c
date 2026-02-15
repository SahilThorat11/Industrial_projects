#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

//      ./cdx        DirectoryPath    
//      argv[0]      argv[1]         
//      argc = 2

/* 
        Accept new directory path
        Call chdir with that path
        call getcwd to check the changed path
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error : Inssufficient arguments\n");
        printf("Use command as : ./cdx DirectoryPath\n");
        return -1;
    }

    if(chdir(argv[1]) == -1)
    {
        printf("Error : Unable to change current directory\n");

        return -1;
    }

    char Buffer[256] = {'\0'};

    getcwd(Buffer, sizeof(Buffer) - 1);

    printf("Current directory changed to %s\n", Buffer);

    return 0;
}