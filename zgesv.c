/* zgesv Example Program Text */
/*
 * ACML version 1.0 Copyright AMD,NAG 2003
 */

#include <acml.h>
#include <stdio.h>

int main(void)
{
#define MMAX 128
#define NMAX 128
#define NRHMAX 128
 const int lda=MMAX, ldb=NMAX;
 int i, info, j, m, n, nrhs;
 int pivot[MMAX];
 doublecomplex a[MMAX*NMAX], b[NMAX*NRHMAX];

 /* These macros allow access to 1-d arrays as though
    they are 2-d arrays stored in column-major order,
    as required by ACML C routines. */
#define A(I,J) a[((J)-1)*lda+(I)-1]
#define B(I,J) b[((J)-1)*ldb+(I)-1]

 printf("ACML example: Solution of system of\n");
 printf("              linear equations using zgesv\n");
 printf("----------------------------------------------------------------\n");
 printf("\n");

 /* Initialize matrix A */
 m = 4;
 n = 4;
 A(1,1) = compose_doublecomplex( 0.18, 0.0);
 A(1,2) = compose_doublecomplex( 0.60, 0.0);
 A(1,3) = compose_doublecomplex( 0.57, 0.0);
 A(1,4) = compose_doublecomplex( 0.96, 0.0);
 A(2,1) = compose_doublecomplex( 0.41, 0.0);
 A(2,2) = compose_doublecomplex( 0.24, 0.0);
 A(2,3) = compose_doublecomplex( 0.99, 0.0);
 A(2,4) = compose_doublecomplex( 0.58, 0.0);
 A(3,1) = compose_doublecomplex( 0.14, 0.0);
 A(3,2) = compose_doublecomplex( 0.30, 0.0);
 A(3,3) = compose_doublecomplex( 0.97, 0.0);
 A(3,4) = compose_doublecomplex( 0.66, 0.0);
 A(4,1) = compose_doublecomplex( 0.51, 0.0);
 A(4,2) = compose_doublecomplex( 0.13, 0.0);
 A(4,3) = compose_doublecomplex( 0.19, 0.0);
 A(4,4) = compose_doublecomplex( 0.85, 0.0);
 A(128,128) = compose_doublecomplex( 0.85, 0.0);

 /* Initialize right-hand-side matrix B */
 nrhs = 1;
 B(1,1) = compose_doublecomplex( 1.0, 0.0);
 B(2,1) = compose_doublecomplex( 2.0, 0.0);
 B(3,1) = compose_doublecomplex( 3.0, 0.0);
 B(4,1) = compose_doublecomplex( 4.0, 0.0);

 printf("Matrix A:\n");
 for (i = 1; i <= m; i++)
   {
     for (j = 1; j <= n; j++)
       printf(" (%9.5f,%9.5f)", A(i,j).real, A(i,j).imag);
     printf("\n");
   }

 printf("\n");
 printf("Right-hand-side matrix B:\n");
 for (i = 1; i <= n; i++)
   {
     for (j = 1; j <= nrhs; j++)
       printf(" (%9.5f,%9.5f)", B(i,j).real, B(i,j).imag);
     printf("\n");
   }

 /* Compute solution of AX = B */
 zgesv(m,nrhs,a,lda,pivot,b,ldb,&info);

 /* Print solution */
 printf("\n");
 printf("Solution matrix X of equations A*X = B:\n");
 for (i = 1; i <= n; i++)
   {
     for (j = 1; j <= nrhs; j++)
       printf(" (%9.5f,%9.5f)", B(i,j).real, B(i,j).imag);
     printf("\n");
   }

 return 0;
}