#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/utsname.h>

//      ./psx            
//      argv[0]
//      argc = 1

/* 
        Open the directory / proc
        Open all sub-directories whose name is integer
        Inside that directory open comm file
        Display the name inside that file
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    struct utsname obj;
    int iRet = 0;

    iRet = uname(&obj);

    if(iRet == -1)
    {
        printf("Error : Unable to fetch system information\n");

        return -1;
    }

    printf("Operating system name : %s\n", obj.sysname);
    printf("Node name : %s\n", obj.nodename);
    printf("Operating system version : %s\n", obj.release);

    return 0;
}