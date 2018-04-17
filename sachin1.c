#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define P1_READ     0
#define P2_WRITE    1
#define P2_READ     2
#define P1_WRITE    3

#define NUM_PIPES   2

char *toggleString(char *argv){

    int i;      

    char *str = malloc(sizeof(argv[1]));  
    strcpy(str, argv    );
    for(i=0;str[i]!='\0';i++)
 	{ 
	 if(str[i]>='A'&&str[i]<='Z')
{
  str[i]+=32 ; 
    } else if (str[i]>='a'&&str[i]<='z') 
{
str[i]-=32;             //Make it uppercase
 }
  }
return str;
}


int inputValidation(int argc, char *argv[]){
  int i;
  
  int c = 0;     
    char str[strlen(argv[1])];  
    
    strcpy(str, argv[1]);     
    if (argc != 2)  
	{
         fprintf(stderr, "\nUsage: %s <string> or <'string 1, string 2', ..., string n'> for multiple strings\n", argv[0]);

     exit(EXIT_FAILURE);  
    } else {
         for(i=0;i<strlen(str);i++) {
        	if(isalpha((int) str[i]))
{
   c = 1; 
 } 

    }
      
         if(c == 0){ 
            printf("\nSorry, The string you entered did NOT contain any Alphabetical Characters\nRun me again, with at least 1 Alphabetical character\n\n");
   exit(EXIT_FAILURE); //Exit on improper input
    }
      return (0);
    }    
}


int main(int argc, char *argv[]) {
   assert(argc>1);
 int fd[2*NUM_PIPES];    
    int len, i;
    pid_t pid;      
 char parent[strlen(argv[1])];   
    char child[strlen(argv[1])];    
    
	if(inputValidation(argc, argv) == 0) 
    	strcpy(parent, argv[1]); 
    
	for (i=0; i<NUM_PIPES; ++i)
    {
        if (pipe(fd+(i*2)) < 0)
        {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }
    }
    if ((pid = fork()) < 0)
    {
        perror("Failed to fork process");
        return EXIT_FAILURE;
    }
    if (pid == 0)
    {
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
        pid = getpid();
        len = read(fd[P2_READ], &child, len);
        if (len < 0)
        {
            perror("Child: Failed to read data from pipe");
            exit(EXIT_FAILURE);
        }
        else if (len == 0)
        {
            fprintf(stderr, "Child: Read EOF from pipe");
        }
        else
        {
            printf("Child(%d): Recieved Message\n\nChild(%d): Toggling Case and Sending to Parent\n",pid, pid);
            if (write(fd[P2_WRITE], toggleString(child), strlen(child)) < 0)
            {
                perror("Child: Failed to write response value");
                exit(EXIT_FAILURE);
}   
        }
      close(fd[P2_READ]);
        close(fd[P2_WRITE]);
              return EXIT_SUCCESS;
    }
    close(fd[P2_READ]);
    close(fd[P2_WRITE]);
             pid = getpid();

                    printf("\nParent(%d): Sending %s to Child\n\n", pid, argv[1]);
    if (write(fd[P1_WRITE], argv[1], strlen(argv[1])) != strlen(argv[1]))
    {
        perror("Parent: Failed to send value to child ");
        exit(EXIT_FAILURE);
    }
    len = read(fd[P1_READ], &parent, strlen(parent));
    if (len < 0)
    {
        perror("Parent: failed to read value from pipe");
        exit(EXIT_FAILURE);
    }
    else if (len == 0)
    {
        fprintf(stderr, "Parent(%d): Read EOF from pipe", pid);
    }
    else
    {
        printf("\nParent(%d): Received %s from Child\n\n", pid, parent);
    }
    
    close(fd[P1_READ]);
    close(fd[P1_WRITE]);
    wait(NULL);
    
    return EXIT_SUCCESS;
}
