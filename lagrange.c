#include <stdlib.h>
#include <stdio.h>

void coefficients(int numberOfPoints, double points[][2]) {
  int i, j;
  
  for (i = 0; i < numberOfPoints; i++) {
    for (j = 0; j < 2; j++) {
      printf("%f\n", points[i][j]);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("You need to provide at least one point.\n");
  } else if (argc % 2 != 1) {
    printf("You need to provide an even number of arguments (x, y)+.\n");
  } else {
    int i, j, numberOfPoints;
    numberOfPoints = (argc - 1) / 2;
    double points[numberOfPoints][2];
    
    for (i = 1; i < argc; i++) {
      points[(i - 1) / 2][(i - 1) % 2] = atof(argv[i]);
    }
    
    coefficients(numberOfPoints, points);
  }
  
  return 0;
}