/*
 * Mitch Gavars
 * Professor Marchiori
 * CSCI 315 Prelab 2 pipe-test.c
 * 9/09/19
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
/*
int Pipe(int pipefd[2]) {
  if (pipe(pipefd) == -1) {
    perror("Pipe Failed");
    exit(-1);
  }
  return 0;
}

int Read(int fd, void *buf, size_t count){
  if (read(fd, buf, count) == -1) {
    perror("Read failed");
    exit(-1);
  }
  return 0;
}


int Write(int fd, const void *buf, size_t count) {
  if (write(fd, buf, count) == -1) {
    perror("Write failed");
    exit(-1);
  }
  return 0;
}
*/


int main(void) {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;
  char EoF = '\0';

  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  pid = fork();

  //Pipe(fd);


  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  if (pid > 0) {
    //parent process
    close(fd[READ_END]);
    //printf("%s", write_msg);
    for (int i = 0; i < strlen(write_msg); i++) {
      write(fd[WRITE_END], &write_msg[i], 1);
    }
    write(fd[WRITE_END], &EoF, 1);
    close(fd[WRITE_END]);
  }
  else {
    //child process
    close(fd[WRITE_END]);
    printf("read \n");
    for (int j = 0; j < strlen(write_msg); j++) {
      if (read(fd[READ_END], &read_msg[j], BUFFER_SIZE) >= 0){
	read(fd[READ_END], &read_msg[j], BUFFER_SIZE);
	printf("%c", read_msg[j]);
        }
    }
    close(fd[READ_END]);
  }
    

  return 0;
  
}
