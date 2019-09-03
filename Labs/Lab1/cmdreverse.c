#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc == 2) {
    char *init_str = argv[1];
    int length = strlen(init_str);
    char temp;
    for(int i = 0; i < length / 2 , i++) {
      temp = init_str[length - 1 - i] = init_str[i];
      init_str[length - 1 - i] = init_str[i];
      init_str[i] = temp;
    }
    printf("%s\n", init_str);
    else {
      printf("You entered %d inputs instead of 1 string\n", argc);
    }

    return 0;
  }
}
