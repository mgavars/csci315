/*
 * Mitch Gavars
 * Professor Marchiori
 * CSCI 315 Prelab3 - mytime.c
 * 9/16/2019
 */

#include <sys/time.h>
#include <unistd.h>
#include <time.h>

int main() {
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);
  printf("%s\n", ctime(&tv));
}
