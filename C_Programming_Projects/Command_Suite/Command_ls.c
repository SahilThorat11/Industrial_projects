#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>

//      ./lsx
//      argv[0]

//      argc = 1

/* 
    Open the current directory(".")
    Read all entries from that directory
    print the name of files 
    Close the directory
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    char *path = ".";

    DIR *dp  = NULL;

    dp = opendir(path);
    if(dp == NULL)
    {
        printf("Error : Unable to Open directory\n");
        return -1;
    }

    struct dirent *dobj;

    while((dobj = readdir(dp)) != NULL)
    {
        printf("%s\n", dobj -> d_name);
    }

    closedir(dp);
    
    return 0;
}