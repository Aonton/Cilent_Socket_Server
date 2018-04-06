#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
  //first argument (argv[1]) should be the Command
  //argc[1] should be passed in quotes " " s that
  //we can have it in one index
  // Ex. ./executor "ls -l"
  if(argc==2)
  {
    int result;
    int pipefd[2];
    char buffer[1024];
    int status;
    FILE *cmd_output;

    result = pipe(pipefd);
    if(result<0)
    {
      printf("Pipe Error");
      exit(0);
    }

    //start forking
    result = fork();
    if(result<0)
    {
      printf("Fork Failed\n");
      exit(0);
    }
    else if(result==0)
    {
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      execl("/bin/sh", "/bin/sh", "-c", argv[1], 0);
      exit(0);
    }
    else
    {
      close(pipefd[1]);

      cmd_output = fdopen(pipefd[0], "r");

      // cmd_output has the command output
      while (fgets(buffer, sizeof buffer, cmd_output) != NULL)
      {
        printf("Data from command: %s\n", buffer);
      }

      wait(&status);
    }
  }
  else
  {
    printf("No command received correctly\n");
  }

}
