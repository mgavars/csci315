/*
 * Mitch Gavars
 * Alan Marchiori
 * Lab 9 - ishell.c
 */

/*
 * PROBLEM 5
 *
 * The functionality I added to my program was what '!!' does in the command
 * line in linux - it repeats the last call. Instead of typing in '!!', you must
 * type in 'repeat' into the command line and it will repeat whatever your last
 * command was.
 */

#include <unistd.h>
#include <string.h>


#include "wrappers.c"

int enterCounter;
char **prevCommand = NULL;

void executeCommand(char **input){
  pid_t pid;
  int status;
  int returnStatus;

  if ((pid = Fork()) == 0) {
    //child process
    
    // Problem 2 - captures termination code
    returnStatus = execvp(*input, input);

    if (returnStatus < 0){
      printf("\n[ishell: program terminated abnormally][%d]\n", returnStatus);
      exit(0);
    }

  }
  else {
    while( wait(&status) != pid);
    printf("\n[ishell: program terminated successfully]\n");
    prevCommand = input;
  }
}

void split(char **input){
  size_t inputLen;
  inputLen = 0;

  char *command = NULL;
  getline(&command, &inputLen, stdin);
 
  char *splits = NULL;
  int arguments = 0;
  
  // Problem 4 - checks to see if the enter button is hit twice
  if (command[0] == '\n'){
    enterCounter++;
    if(enterCounter == 2) {
      input[0] = "ls";
      input[1] = "./";
      enterCounter = 0;
      executeCommand(input);
    }
    split(input);
  }
 
  // Problem 5
  else if(strcmp(command,"repeat\n") == 0) {
    input = prevCommand;
    arguments = strlen(command);
  }

  else {
    while((splits = strtok_r(command, " ", &command))) {
      
      // Checks for a newline character at the end of each parse
      if (splits[strlen(splits)-1] == '\n'){
	splits[strlen(splits)-1] = 0;
      }

      // Problem 3 - checks for a semicolon to execute two commands
      if (splits[strlen(splits)-1] == ';'){
	splits[strlen(splits)-1] = 0;
	input[arguments] = splits;
	arguments += 1;
	executeCommand(input);
	//printf("\nexecuted first command\n");
      }
      else {
	input[arguments] = splits;
	arguments += 1;
      }
      if (arguments > 99) {
	printf("ERROR - too many  arguments");
	break;
      }
    } 
  } 
  
  
  input[arguments] = '\0';

}



int main(int argc, char *argv[]) {
  char *input[100];

  while(1) {
    printf("\nishell> ");
    split(input);
    if (strcmp(input[0], "exit") == 0) {
      break;
    }
    if (strcmp(input[0], "repeat") == 0){
      executeCommand(input);
    }
    else{
      executeCommand(input);
    }   
  }
  return 0;
}
