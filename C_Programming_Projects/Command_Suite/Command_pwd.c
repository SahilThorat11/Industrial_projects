#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

//      ./pwdx            
//      argv[0]
//      argc = 1

/* 
        Call the system call getcwd    (cwd - Current Working Directory)
        Print the result of getcwd
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    char Buffer[1024] = {'\0'};

    getcwd(Buffer, sizeof(Buffer));

    printf("\nPath\n");
    printf("----\n");
    printf("%s\n\n", Buffer);

    return 0;
}