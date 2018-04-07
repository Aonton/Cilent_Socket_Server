#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* INPUT: input a string/char* that is
   the command that the user wants to execute
   on the server. The command should be put in
   quotes " " if there are spaces.
   EX. command = "cat Makefile"
*/

/* OUPUT:
   cmd_output is a pointer to the ouput of
   the command. This function returns that
   pointer.
   To print the output of that command ...
   EX......
   while (fgets(buffer, sizeof buffer, cmd_output) != NULL)
   {
     printf("Data from command: %s\n", buffer);
   }
*/

FILE* executor(char* command)
{
  FILE* cmd_output;
  if(command!=NULL)
  {
    int result;
    int pipefd[2];
    char buffer[1024];
    int status;

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
      dup2(pipefd[1], STDERR_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      execl("/bin/sh", "/bin/sh", "-c", command, 0);
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

  return cmd_output;
}
