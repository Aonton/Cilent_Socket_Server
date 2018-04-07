#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void executor(command)
{
  //first argument (argv[1]) should be the Command
  //argc[1] should be passed in quotes " " s that
  //we can have it in one index
  // Ex. ./executor "ls -l"
  if(command!=NULL)
  {
    int result;
    char buffer[1024];
    int status;
    FILE *cmd_output;
    char path[15] = " &> output.txt";

    //start forking
    result = fork();
    if(result<0)
    {
      printf("Fork Failed\n");
      exit(0);
    }
    else if(result==0)
    {
      execl("/bin/sh", "/bin/sh", "-c", strcat(command,path) , 0);
      exit(0);
    }
    else
    {
      wait(&status);
    }
  }
  else
  {
    printf("No command received correctly\n");
  }

}
