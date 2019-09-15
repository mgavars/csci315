/*
 * Mitch Gavars
 * Professor Marchiori
 * CSCI 315 Prelab 2 upper.c
 * 9/09/19
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <ctype.h>

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
  int p2c[2];
  int c2p[2];
  pid_t pid;
  char EoF = '\0';
  int status;

  if (pipe(p2c) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  if (pipe(c2p) == -1) {
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
    close(p2c[READ_END]);
    close(c2p[WRITE_END]);
    //printf("%s", write_msg);
    for (int i = 0; i < strlen(write_msg); i++) {
      write(p2c[WRITE_END], &write_msg[i], BUFFER_SIZE);
    }
    write(p2c[WRITE_END], &EoF, BUFFER_SIZE);
    close(p2c[WRITE_END]);

    wait(&status);
    //printf("we made it here\n");
    
    for (int c = 0; c < strlen(write_msg); c++) {
      //printf("c");
      read(c2p[READ_END], &read_msg[c], BUFFER_SIZE);
      printf("%c", read_msg[c]);
    }
    
    printf("\n");

    close(c2p[READ_END]);
  }
  else {
    //child process
    close(p2c[WRITE_END]);
    close(c2p[READ_END]);
    const char *filler;
    printf("read\n");

    for (int j = 0; j < strlen(write_msg); j++) {
      //printf("a");
      
      read(p2c[READ_END], &read_msg[j], BUFFER_SIZE);
      filler = toupper(read_msg[j]);
      printf("%c", read_msg[j]);
      write(c2p[WRITE_END], &filler, BUFFER_SIZE);
      
    }
    close(p2c[READ_END]);
    printf("\n");
   
    //write(c2p[WRITE_END], &EoF, 1);
    
    
    close(c2p[WRITE_END]);
  }
    

  return 0;
  
}
