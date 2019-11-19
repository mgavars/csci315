/* 
 * Mitch Gavars
 * CSCI 315
 * Alan Marchiori
 * Prelab 10 - fdump.c
 * 11/19/19
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hexdump.h"

int main(int argc, char *argv[]){
  char *fileName = argv[1];
  unsigned int offset = (unsigned int)atoi(argv[2]);
  unsigned int size = (unsigned int)atoi(argv[3]);

  if (sizeof(fileName) == 0){
    printf("No file included --- exiting");
    return 0;
  }
  if (offset == 0) {
    printf("No offset provided --- exiting");
    return 0;
  }
  if (size == 0) {
    printf("No size provided --- exiting");
    return 0;
  }

  FILE *fileRead;
  unsigned char *buffer = (unsigned char *)malloc(size + 1);
  unsigned long fileLen;

  fileRead = fopen(fileName, "r");

  fseek(fileRead, 0, SEEK_END);
  fileLen = ftell(fileRead);
  fseek(fileRead, 0, SEEK_SET);

  fread(buffer, sizeof(char), size, fileRead);
  hexdump(buffer, size);
  fclose(fileRead);
  printf("\n");
  return 0;


}
