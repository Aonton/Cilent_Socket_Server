#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* Amy Feng
  April 7, 2018
  Note: For the person adapting this
        function into the client/server
        code. My advice is either copy this
        function into the server file or
        use a file pointer to reference this
        function. I suggest the latter for
        code clarity. The client code should
        send the command to the server and
        the server should take that command
        and pass it to this function (see below
        for how to pass arguments into this function).
        The server should take the file pointer returned
        from this function (see below for info on the return
        variable). The server should send the output line by
        line to the client (see below in the ouput section for
        suggestion on how to do this)
*/

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

/* This function executes a command
   and return the command's ouput.
*/
FILE* executor(char* command)
{
  // cmd_output has the command output
  FILE* cmd_output = NULL;

  // command should not be NULL
  // server code should check to make
  // sure the file pointer (return value)
  // is not null. If it is, please handle
  // it how you see fit.
  if(command!=NULL)
  {
    // add command to the logfile
    FILE * logfile_fp;
    logfile_fp = fopen("logfile.txt", "a+");
    fputs(command, logfile_fp);

    int result;
    int pipefd[2];
    char buffer[1024];
    int status;

    // creating pipes
    result = pipe(pipefd);

    // checks for pipe creation error
    if(result<0)
    {
      printf("Pipe Error");
      exit(0);
    }

    //start forking
    result = fork();

    // checks for fork creation error
    if(result<0)
    {
      printf("Fork Failed\n");
      exit(0);
    }
    // child process
    else if(result==0)
    {
      // directing STDOUT and STDERR consoles
      // to pipes (pipefd)
      dup2(pipefd[1], STDOUT_FILENO);
      dup2(pipefd[1], STDERR_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);

      // executes the command
      // since the output and error buffers
      // have been redirected, the output will
      // not go to the console and instead go into
      // the pipes
      execl("/bin/sh", "/bin/sh", "-c", command, 0);
      exit(0);
    }
    // parent process
    else
    {
      close(pipefd[1]);

      // dumping data from pipes into
      // file pointer (cmd_output)
      cmd_output = fdopen(pipefd[0], "r");

      // This just displays the output/error.
      // This can be remove later or kept.

      while (fgets(buffer, sizeof buffer, cmd_output) != NULL)
      {
        // printf("Data from command: %s\n", buffer);

        // write to a logfile
        fputs(buffer, logfile_fp);
      }
      fclose(logfile_fp);

      // parent processes must wait for the child process
      wait(&status);
    }
  }
  // Error message for null command
  else
  {
    printf("No command received correctly\n");
  }

  return cmd_output;
}
