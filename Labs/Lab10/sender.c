
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char input[100];
  FILE *fptr = fopen("channel.txt","w");

  while(1) {


    printf("\nsender> ");
    scanf("%s", input);
    strcat(input, "\n");
    if (strcmp(input, "exit\n") == 0) {
      break;
    }
    else {
      
      //printf("%s", input);
      fprintf(fptr, input);
    }
  }
  fclose(fptr);
  return 0;
}
