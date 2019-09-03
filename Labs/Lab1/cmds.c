#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if (argc == 5) {
    char c = argv[1][0];
    int i = atoi(argv[2]);
    float f = atof(argv[3]);
    char *s = argv[4];

    printf("character : %c\n", c);
    printf("int : %d\n", i);
    printf("float : %f\n", f);
    printf("string : %s\n", s);
  }
  else { 
    printf("You entered %d inputs instead of 4\n", argc);
  }
  return 0;
}
