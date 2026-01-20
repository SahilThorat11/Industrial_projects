//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Header File Inclusion
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>    
#include<stdlib.h>    
#include<unistd.h>    
#include<stdbool.h>  
#include<string.h>   

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define SATRT 0
#define CURRENT 1
#define END 2

#define REGULARFILE 1
#define SPECIALFILE 2

#define EXECUTE_SUCCESS 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Macros for Error handling
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  User Defined Structures
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : BootBlock
//  Description    : Holds the information to boot the OS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : SuperBlock
//  Description    : Holds the information about the file system
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};
                                                                                                                                                                        
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : Inode
//  Description    : Holds the information about the file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    char *Buffer;             // Data Block
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : FileTable
//  Description    : Holds the information about opened file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;     // From where to read
    int WriteOffset;    // from where to write
    int Mode;           // file open in which mode or which permission is give to open file
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure Name : UAREA
//  Description    : Holds the information about process
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Global variable or objects used in the project
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitializeUAREA
//  Description :       It is used to initialize UAREA members
//  Author :            Sahil Rajaram Thorat
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void InitializeUAREA()
{
    strcpy(uareaobj.ProcessName, "Myexe");

    int i = 0;

    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }

    printf("Marvellous CVFS : UAREA gets initialized successfully\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     InitializeSuperBlock
//  Description :       It is used to initialize Super block members
//  Author :            Sahil Rajaram Thorat
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void InitializeSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super block gets initialized successfully\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateDILB
//  Description :       It is used to create Linkedlist of Inodes
//  Author :            Sahil Rajaram Thorat
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));

        strcpy(newn -> FileName ,"\0");
        newn -> InodeNumber = i;
        newn -> FileSize = 0;
        newn -> ActualFileSize = 0;
        newn -> FileType = 0;
        newn -> ReferenceCount = 0;
        newn -> Permission = 0;
        newn -> Buffer = NULL;
        newn -> next = NULL;

        if(temp == NULL)                        // LL is empty
        {
            head = newn;
            temp = head;
        }
        else                                    // LL contains atleast one node
        {
            temp -> next = newn;
            temp = temp -> next;            
        }
    }

    printf("Marvellous CVFS : DILB created successfully\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     StartAuxillaryDataInitialization
//  Description :       It is used to all such functions which are used to initialize auxyilary data.
//  Author :            Sahil Rajaram Thorat
//  Date :              13/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void StartAuxillaryDataInitialization()
{
    strcpy(bootobj.Information, "Booting process of Marvellous CVFS is done");

    printf("%s\n", bootobj.Information);

    InitializeSuperBlock();

    CreateDILB();

    InitializeUAREA();

    printf("Marvellous CVFS : Auxillary data initialized successfully\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     DisplayHelp
//  Description :       It is used to diplay the help page.
//  Author :            Sahil Rajaram Thorat
//  Date :              14/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("\n-----------------------------------------------------------------------------\n");
    printf("------------------------- Marvellous CVFS Help Page -------------------------\n");
    printf("-----------------------------------------------------------------------------\n");

    printf("man    : It is used to display manual page\n");
    printf("clear  : It is used to clear the terminal\n");
    printf("creat  : It is used to create new file\n");
    printf("write  : It is used to write the data into the file\n");
    printf("read   : It is used to read the data from the file\n");
    printf("stat   : It is used to display statistical information\n");
    printf("unlink : It is used to delete the file\n");
    printf("exit   : It is used to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------------------------------------\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     ManPageDisplay
//  Description :       It is used to diplay Man page.
//  Author :            Sahil Rajaram Thorat
//  Date :              14/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls", Name) == 0)
    {
        printf("\nAbout : It is used to list the names of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man", Name) == 0)
    {
        printf("\nAbout : It is used to display manual page\n");
        printf("Usage : man Command_name\n");
        printf("Command_name : It is the name of command\n");
    }
    else if(strcmp("exit", Name) == 0)
    {
        printf("\nAbout : It is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else if(strcmp("clear", Name) == 0)
    {
        printf("\nAbout : It is used to clear the shell\n");
        printf("Usage : clear\n");
    }
    else
    {
        printf("No manual entry for %s\n", Name);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     IsFileExist
//  Description   :     It is used to check whether file is already exist or not.
//  Input         :     It accepts file name 
//  Output        :     It returns true or false
//  Author        :     Sahil Rajaram Thorat
//  Date          :     16/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsFileExist(
                    char *name     // File name
                )

                {
                    PINODE temp = head;
                    bool bFlag = false;

                    while(temp != NULL)
                    {
                        if((strcmp(name, temp -> FileName) == 0) && (temp -> FileType == REGULARFILE))
                        {
                            bFlag = true;
                            break;
                        }
                        temp = temp -> next;
                    }

                    return bFlag;
                } // End of IsFileExit

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     CreateFile
//  Description   :     It is used to crate new regular file.
//  Input         :     It accepts file name and permissions 
//  Output        :     It returns the file descriptor
//  Author        :     Sahil Rajaram Thorat
//  Date          :     16/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int CreateFile(
                    char *name,         // Name of new file
                    int permission      // Permission of the file
                )
                {
                    PINODE temp = head;
                    int i = 0;

                    printf("Total number of Inodes remaining : %d\n", superobj.FreeInodes);

                    // If name is missing
                    if(name == NULL)
                    {
                        return ERR_INVALID_PARAMETER;
                    }

                    // If the permission value is wrong
                    // permission -> 1 = READ
                    // permission -> 2 = WRITE
                    // permission -> 3 = READ + WRITE
                    if(permission < 1 || permission > 3)
                    {
                        return ERR_INVALID_PARAMETER;   
                    }

                    // If the Inodes are full
                    if(superobj.FreeInodes == 0)
                    {
                        return ERR_NO_INODES;
                    }

                    // If file is already present
                    if(IsFileExist(name) == true)
                    {
                        return ERR_FILE_ALREADY_EXIST;
                    }

                    // Search empty Inode
                    while(temp != NULL)
                    {
                        if(temp -> FileType == 0)
                        {
                            break;
                        }
                        temp = temp -> next;
                    }

                    if(temp == NULL)
                    {
                        printf("There is no Inode\n");
                        return ERR_NO_INODES;
                    }

                    // Search for empty UFDT entry
                    // NOTE : 0,1,2 are reserved
                    for(i = 3; i < MAXOPENFILES; i++)
                    {
                        if(uareaobj.UFDT[i] == NULL)
                        {
                            break;
                        }
                    }

                    // UFDT is full
                    if(i == MAXFILESIZE)
                    {
                        return ERR_MAX_FILES_OPEN;
                    }

                    // Allocate memory for file table
                    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

                    // Initialize file table
                    uareaobj.UFDT[i] -> ReadOffset = 0;
                    uareaobj.UFDT[i] -> WriteOffset = 0;
                    uareaobj.UFDT[i] -> Mode = permission;

                    // Connect File Table with Inode
                    uareaobj.UFDT[i] -> ptrinode = temp;

                    // Initialize elements of Inode
                    strcpy(uareaobj.UFDT[i] -> ptrinode -> FileName, name);
                    uareaobj.UFDT[i] -> ptrinode -> FileSize = MAXFILESIZE;
                    uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
                    uareaobj.UFDT[i] -> ptrinode -> FileType = REGULARFILE;
                    uareaobj.UFDT[i] -> ptrinode -> ReferenceCount = 1;
                    uareaobj.UFDT[i] -> ptrinode -> Permission = permission; 

                    // Allocate memory for files data
                    uareaobj.UFDT[i] -> ptrinode -> Buffer = (char*)malloc(MAXFILESIZE);

                    superobj.FreeInodes--;

                    return i;  // File descriptor (FD)
                } // End of CreateFile 

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Function Name :     LsFile
//  Description   :     It is used to list all file.
//  Input         :     Nothing
//  Output        :     Nothing
//  Author        :     Sahil Rajaram Thorat
//  Date          :     16/01/2026
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void LsFile()
{
    PINODE temp = head;

    printf("\n-----------------------------------------------------------------------------\n");
    printf("---------------------- Marvellous CVFS Files Information --------------------\n");
    printf("-----------------------------------------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp -> FileType != 0)
        {
            printf("%d\t%s\t%d\n", temp -> InodeNumber, temp -> FileName, temp -> ActualFileSize);
        }
        
        temp = temp -> next;
    }

    printf("\n-----------------------------------------------------------------------------\n");
} // End of LsFile

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Entry point function of the project   
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitialization();

    printf("\n-----------------------------------------------------------------------------\n");
    printf("--------------------- Marvellous CVFS started sucessfully -------------------\n");
    printf("-----------------------------------------------------------------------------\n");

    // Infinite Listening Shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str, sizeof(str), stdin);        // Scanf("%s",str);

        iCount = sscanf(str,"%s %s %s %s %s",Command[0],Command[1],Command[2],Command[3],Command[4]);

        fflush(stdin);

        if(iCount == 1)
        {
            // Marvellous CVFS : > exit
            if(strcmp("exit",Command[0]) == 0)
            {
                printf("Thank you for using Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
            }

            // Marvellous CVFS : > ls
            else if(strcmp("ls",Command[0]) == 0)
            {
                LsFile();
            }

            // Marvellous CVFS : > help
            else if(strcmp("help",Command[0]) == 0)
            {
                DisplayHelp();
            }

            // Marvellous CVFS : > clear
            else if(strcmp("clear",Command[0]) == 0)
            {
                #ifdef _WIN32        // If windows
                    system("cls");
                #else                // If linux/macOS
                    system("clear")
                #endif
            }
        } // End of if 1
        else if(iCount == 2)
        {
            // Marvellous CVFS : > man ls
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
        } // End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > crear Ganesh.txt 3
            if(strcmp("creat",Command[0]) == 0)
            {
                iRet = CreateFile(Command[1], atoi(Command[2]));   // Inbuilt function for axii to int

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("ERROR : Unable to create the file as parameters are invalid\n");
                    printf("Please refer man page\n");
                }

                if(iRet == ERR_NO_INODES)
                {
                    printf("ERROR : Unable to create file as there is no inode\n");
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("ERROR : Unable to create file because the file is already present\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("ERROR : Unable to create file\n");
                    printf("Max opened files limit reached\n");
                }

                printf("File gets successfully created with FD %d\n", iRet);
            }
        } // End of else if 3
        else if(iCount == 4)
        {} // End of else if 4
        else
        {
            printf("Command not found\n");
            printf("Please refer help option to get more information\n");
        } // End of else
    } // End of while

    return 0;
} // End of main