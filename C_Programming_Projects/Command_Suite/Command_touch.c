#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

//      ./touchx        FileName    
//      argv[0]         argv[1]         
//      argc = 2

/* 
        Accept file name from command line
        Check Whether file is existing or not
        If it is existing return 
        If it is not existing 
        Create that file
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error : Inssufficient arguments.\n");
        printf("Use command as : ./touchx FileName.\n");
        return -1;
    }

    if(access(argv[1], F_OK) == 0)
    {
        return 0;
    }
    else
    {
        creat(argv[2], 0777);
    }

    return 0;
}