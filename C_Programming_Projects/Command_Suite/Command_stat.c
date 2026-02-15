#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>

//      ./statx        FileName    
//      argv[0]         argv[1]         
//      argc = 2

/* 
        Accept file name from command line
        Call access to check existance of file
        Call stat system call to get files meta data
        Display the metadata
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error : Inssufficient arguments\n");
        printf("Use command as : ./statx FileName\n");
        return -1;
    }

    if(access(argv[1], F_OK) == 0)
    {
        struct stat sobj;
        int iRet = 0;

        iRet = stat(argv[1], &sobj);

        if(iRet == -1)
        {
            printf("Error : Unable to fetch statistical information\n");
            return -1;
        }

        printf("File name : %s\n", argv[1]);
        printf("File size : %ld bytes\n", (long)sobj.st_size);
        printf("Inode Number : %ld\n", (long)sobj.st_ino);
    }
    else
    {
        printf("Error : File not found\n");
        return -1;
    }

    return 0;
}p