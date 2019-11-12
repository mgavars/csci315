#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double Student_idf(int, int);

int main(int argc, char *argv[]) {

  if (argc < 3) {
    printf("usage: student [L confidence level] [n number of samples]\n");
    exit(-1);
  }

  printf("%lf\n\n", Student_idf(atoi(argv[2])-1, atof(argv[1])));
  
}
