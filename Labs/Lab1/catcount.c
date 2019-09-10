#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int arc, char *argv[]){
  print_environment();
  int pid;
  int status;
  // printf("beginning program\n");
  if ((pid = fork()) == 0){
    //child process
    //printf("child 1 process created\n");
    execlp("/bin/cat/",argv[0],(char *)NULL);
    //printf("working\n");
    exit(status);
    // printf("this should not print because the process should be terminated\n");

  }
  else {
    //parent process
    wait(&status);
    // printf("child 1 process terminated\n");
    if ((pid = fork()) == 0) {
      //child 2 process
      //printf("child 2 process created\n");
      execlp("/usr/bin/wc/",argv[0],(char *)NULL);
      //printf("working\n");
      exit(status);

    }
    wait(&status);
    //printf("child 2 process terminated\n");
    exit(status);
  }
}

void print_environment(void){
  extern char **environ;
  for (int i = 0; i < sizeof(environ)/sizeof(char); i++){
    for (int j = 0; j < sizeof(*environ)/sizeof(char); j++) {
      printf("environ[%d][%d] = %c\n", i, j, environ[i][j]);
    }
  }
}
