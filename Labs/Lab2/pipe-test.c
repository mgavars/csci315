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

int main(void) {
  char write_msg[BUFFER_SIZE] = "Greetings";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;

  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }

  if (pid > 0) {
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    close(fd[WRITE_END]);
  }
  else {
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("read %s", read_msg);
    close(fd[READ_END]);
  }

  return 0;
}
