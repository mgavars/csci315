#include <stdio.h> 
#include <unistd.h>

int main() {
  int parentCounter = 0;
  int c1Counter = 0;
  int c2Counter = 0;
  pid_t fork_child1_id = fork();

  while (parentCounter >= 0) {
    if (fork_child1_id == 0){
      c1Counter += 1;
      printf("child 1: %d \n", c1Counter);
    }
    else {

      pid_t fork_child2_id = fork();
      while (parentCounter >= 0) {
	if (fork_child2_id == 0){
	  c2Counter += 1;
	  printf("child 2: %d \n", c2Counter);
	} 
      
      else {
	while (parentCounter >= 0) {
	  parentCounter += 1;
	  printf("parent: %d \n", parentCounter);
	}
      }
      }
    }
  }
  return 0;
}


