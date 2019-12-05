/*
 * Mitch Gavars
 * CSCI 315
 * Alan Marchiori
 * Lab 10 - traverse.c
 */

#include "read_dir.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// function prototypes
void process(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

// main function
int main(int argc,char *argv[]) {

  if (2 != argc) {
    printf(" usage: %s dirpath\n", argv[0]);
    exit(-1);
  }
  else {
    // pass in the starting directory
    process(argv[1]);       
  }
  
  return 0;
}

// traverse a directory tree applying a function when a file is found
void process(char *root)
{
  int numOfFiles = 0;
  int numOfDirec = 0;
  que_t nameq;
  char dname[MAXLENGTH];
  char cname[MAXLENGTH];
  char prefix[MAXLENGTH];

  struct stat file_info;
  unsigned int fd;

  off_t totalFileSizes = 0;
  off_t smallestFileSize = 10000000000000;
  off_t largestFileSize = 0;

  time_t leastRecent = time(NULL);
  time_t mostRecent = 0;
  //printf("%jd\n", (intmax_t)mostRecent);
  char LRMFilename[MAXLENGTH];
  char MRMFilename[MAXLENGTH];

  
  
  struct dirent *dp;
  DIR *dirp;

    initq(&nameq);
    enqueue(root,&nameq);

    while (true != queue_empty(nameq)) {
      peek_front(dname,nameq); 
      dequeue(&nameq);
      dirp = opendir(dname);

      
            
      
      if (dirp != NULL) { // it is a directory

	printf("directory : %s\n",dname);
	strncpy(prefix, dname, MAXLENGTH);
	strncat(prefix,"/", MAXLENGTH);

	if (lstat(dname, &file_info)==0){
	  if (S_ISLNK(file_info.st_mode)){
	    printf("%s is a symbolic link\n", dname);
	  }
	  else {
	
	    for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
	      if ((strcmp(dp->d_name,"..") != 0) && 
		  (strcmp(dp->d_name,".") != 0)) {
	    
		// prevent from infinite loop
		strncpy(cname, prefix, MAXLENGTH);
	    
		// concatenate the prefix
		strncat(cname, dp->d_name, MAXLENGTH);  
		enqueue(cname,&nameq);
	      }
	    }
	  }
	}
	closedir (dirp);
	numOfDirec++;
      } else { 
	// test if it is a regular file and not a device or link -- TO-DO
	fd = open(dname, O_RDONLY);
	if (-1 == fd) {
	  perror(" Failed to open read only file - ");
	  exit(-1);
	}
	else {
	  if (fstat(fd, &file_info) == 0){
	    // if this is a regular file, then process it -- TO-DO
	    if (S_ISLNK(file_info.st_mode)){
	      printf("found a symbolic link");
	    }
	    if (S_ISREG(file_info.st_mode)){
	      printf(" processing file: %s\n", dname);

	      // find the largest and smallets file sizes
	      if(file_info.st_size < smallestFileSize){
		smallestFileSize = file_info.st_size;
	      }
	      if(file_info.st_size > largestFileSize){
		largestFileSize = file_info.st_size;
	      }

	      totalFileSizes += file_info.st_size;
	      numOfFiles++;

	      //find the most recent and least recently modified files
	      if(file_info.st_mtime > mostRecent){
		strncpy(MRMFilename, dname, MAXLENGTH);
		mostRecent = file_info.st_mtime;
	      }
	      if(file_info.st_mtime < leastRecent){
		strncpy(LRMFilename, dname, MAXLENGTH);
		leastRecent = file_info.st_mtime;
	      }
	    }
	  } 
	  close(fd);
	}
	
      }      
    } // while
    
    int avgFileSize = (int)totalFileSizes;
    printf(" \n a total of %d files were counted\n",numOfFiles);
    printf(" a total of %d directories were counted\n",numOfDirec);
    printf(" smallest file found is size: %d\n", (int)smallestFileSize);
    printf(" largest file found is size: %d\n", (int)largestFileSize);
    printf(" average file size is: %d\n", avgFileSize/numOfFiles);
    printf(" least recently modified file is: %s\n", LRMFilename);
    printf(" most recently modified file is: %s\n", MRMFilename);


}

// initialize queue data structure
void initq(que_t *q) {
  q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
  if (NULL == q.head) {
     return true;
  } else {
    return false;
  }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
  item_t *temp;
  
  temp = (item_t *)malloc(sizeof(item_t));
  strncpy(temp->name,name,MAXLENGTH);
  temp->next = NULL;
  
  if (true == queue_empty(*q)) {
    q->head = temp;
    q->tail = temp;
  } else {
    q->tail->next = temp;
    q->tail = q->tail->next;
  }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
  item_t *temp;
  
  if (true == queue_empty(*q)) {
    printf(" error in dequeue \n");
    exit(-1);
  } else {
    temp = q->head;
    q->head = q->head->next;
    free(temp);
  }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
  if (true == queue_empty(q)) {
    printf(" error in dequeue \n");
     exit(-1);
  } else {
    strncpy(name, q.head->name, MAXLENGTH);
  }
} 
