/*********************************************
 * Id: vorc2804
 *
 * This program takes in arguments from the user that represent the coefficients
 * of an augmented matrix for some linear system of unknown variables.
 * It then performs Gaussian Elimination on the matrix, but does not determine
 * consistency or the span of the matrix.
 *********************************************/
#include "stdio.h"
#include "stdlib.h"
#include "float.h"

#define FLT_NULL FLT_MAX

void print_matrix(int, float**);
void doGaussianElim(int, float**);

/*
 * Driver function for the program.  The user supplies the number of rows the
 * matrix is to have, followed by the constants in each position of the
 * augmented matrix.
 * 
 * @param argc: the number of arguments passed in by the user
 * @param argv[0]: the name of the executable that runs this file
 * @param argv[1]: the number of rows in the matrix
 * @param argv[2..argc - 1]: coefficients in the matrix
 */
int main(int argc, char* argv[]){
   int numRows = atoi(argv[1]);                                    /* number of rows in matrix */
   int numConstants = argc - 2;
   int coefficientsPerRow = numConstants / numRows;   
   float** matrix = malloc((numRows + 1) * sizeof(float*));  /* reserve in memory a 2D array of floats that will be the coefficient matrix */
   matrix[numRows] = NULL;

   int i;
   int column = 0;
   int row = 0;
   for (i = 2; i < argc; i++){
      if (column == 0){
         matrix[row] = malloc((coefficientsPerRow + 1) * sizeof(float));
         matrix[row][coefficientsPerRow] = FLT_NULL;
         row++;
      }

      matrix[row - 1][column] = atof(argv[i]);
      column++;

      if (column % coefficientsPerRow == 0){
         column = 0;
      }
   }

   doGaussianElim(numRows, matrix);

   for (i = 0; i < numRows + 1; i++){
      free(matrix[i]);
   }
   free(matrix);
   return 0;
}

/*
 * Performs the Gaussian Elimination on the matrix that was created
 * from the parameters passed in at run time.  Does not return as
 * the matrix is stored on the heap as an array of pointers.
 * 
 * @param numRows: the number of rows in the matrix passed in
 * @param matrix: the coefficient matrix (augmented) that we are performing 
 * the Gaussian Elimination on
 */
void doGaussianElim(int numRows, float** matrix){
   int i, j, k;
   float save;

   print_matrix(numRows, matrix);

   for (i = 0; i < numRows - 1; i++){
      for (j = i + 1; j < numRows; j++){
         save = matrix[j][i];
         for (k = i; k < numRows + 1; k++){
            matrix[j][k] = matrix[j][k] - matrix[i][k] * save / matrix[i][i];
         }
      }
      print_matrix(numRows, matrix);
   }
}

/*
 * Prints the matrix.  This is called before the matrix is modified,
 * and then at each step of the Gaussian Elimination process (including
 * the finished state).
 * 
 * @param numRows: the number of rows in the matrix
 * @param matrix: the matrix to be printed
 */
void print_matrix(int numRows, float** matrix){
   int m;
   int n;

   for (m = 0; matrix[m] != NULL; m++){
      n = 0;
      while (matrix[m][n] != FLT_NULL){
         if (matrix[m][n + 1] == FLT_NULL){
            printf("%.2lf \n", matrix[m][n]);
         }
         else{
            printf("%.2lf ", matrix[m][n]);
         }
         n++;
      }
   }
   printf("\n");
}