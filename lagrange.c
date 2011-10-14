#include <stdlib.h>
#include <stdio.h>

void coefficients(int numberOfPoints, long double points[][2]);
void basisCoefficients(int indexToSkip, int numberOfPoints, long double points[][2], long double basisCoefficientsArray[]);

void coefficients(int numberOfPoints, long double points[][2]) {
  int i, j;
  long double coefficientsArray[numberOfPoints], basisCoefficientsArray[numberOfPoints];
  
  for (i = 0; i < numberOfPoints; i++) {
    coefficientsArray[i] = 0;
  }
  
  for (i = 0; i < numberOfPoints; i++) {
    basisCoefficients(i, numberOfPoints, points, basisCoefficientsArray);
    
    for (j = 0; j < numberOfPoints; j++) {
      coefficientsArray[j] += basisCoefficientsArray[j];
    }
  }
  
  printf("[");
  
  for (i = 0; i < numberOfPoints; i++) {
    printf("%Lf", coefficientsArray[i]);
    
    if (i < numberOfPoints - 1) {
      printf(", ");
    }
  }
  
  printf("]\n");
}

void basisCoefficients(int indexToSkip, int numberOfPoints, long double points[][2], long double basisCoefficientsArray[]) {
  int i, j, k;
  long double oldValue;
  long double constant = points[indexToSkip][1];
  
  for (i = 0; i < numberOfPoints; i++) {
    if (i != indexToSkip) {
      constant *= 1 / (points[indexToSkip][0] - points[i][0]);
    }
  }
  
  basisCoefficientsArray[0] = 1;
  
  for (i = 0; i < numberOfPoints; i++) {
    if (i != indexToSkip) {
      k = (i > indexToSkip ? i : i + 1);
      oldValue = basisCoefficientsArray[j];
      basisCoefficientsArray[k] = 0;
      
      for (j = k; j >= 0; j--) {
        if (j < k) {
          basisCoefficientsArray[j] *= -points[i][0];
        }
        
        if (j > 0) {
          basisCoefficientsArray[j] += basisCoefficientsArray[j - 1];
        }
      }
    }
  }
  
  for (i = 0; i < numberOfPoints; i++) {
    basisCoefficientsArray[i] *= constant;
  }
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("You need to provide at least one point.\n");
  } else if (argc % 2 != 1) {
    printf("You need to provide an even number of arguments (x, y)+.\n");
  } else {
    int i, j, numberOfPoints;
    numberOfPoints = (argc - 1) / 2;
    long double points[numberOfPoints][2];
    
    for (i = 1; i < argc; i++) {
      points[(i - 1) / 2][(i - 1) % 2] = atof(argv[i]);
    }
    
    coefficients(numberOfPoints, points);
  }
  
  return 0;
}