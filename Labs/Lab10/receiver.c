#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  char *input;
  FILE *fptr = fopen("channel.txt","r");


  while(1) {

    if (feof(fptr)){
      break;
    }
    
    else{
      fgets(input, 100000, fptr);
      printf("receiver [msg arrival]: %s", input);
    }
    //printf(input);
  }
  fclose(fptr);
  return 0;
}
