#include "stdio.h"
#include "stdlib.h"
#include "float.h"

#define DBL_NULL DBL_MAX

void print_matrix();

int main(int argc, char* argv[]){
    int numEquations = atoi(argv[1]);                                               /* number of rows in matrix */
    int invisCoefficients = (argc - 2) % numEquations;                              /* number of zeroes to add to the final row if the number of arguments / number of rows is not an integer value */
    int numCoefficients = argc - 2 - numEquations + invisCoefficients;              /* number of coefficients (LHS of linear system) */
    int coefficientsPerRow = ((argc - 2 + invisCoefficients) / numEquations) - 1;   
    double* constants = malloc((numEquations + 1)*sizeof(double));                  /* reserve in memory the number of constants (equal to number of equations) (RHS of linear system) */
    double** coefficientMatrix = malloc(numEquations * sizeof(double*));            /* reserve in memory a 2D array of floats that will be the coefficient matrix */
    constants[numEquations] = DBL_NULL;

    int i;
    int j = 0;
    int k = 0;
    int offset = 0;
    for (i = 2; i + offset < argc; i++){
        if (j == 0){
            coefficientMatrix[k] = malloc((coefficientsPerRow + 1) * sizeof(double));
            k++;
        }
        
        coefficientMatrix[k - 1][j] = atof(argv[i + offset]);
        j++;

        if (j % coefficientsPerRow == 0){
            coefficientMatrix[k - 1][j] = DBL_NULL;
            j = 0;
            offset++;
        }
    }

    int m;
    int n;
    printf("[");
    for (m = 0; m < numEquations; m++){
        n = 0;
        while (coefficientMatrix[m][n] != DBL_NULL){
            if (m > 0 && n == 0){
                printf(" %.2lf ", coefficientMatrix[m][n]);
            }
            else{
                printf("%.2lf ", coefficientMatrix[m][n]);
            }
            n++;
        }
        if (m != numEquations - 1){
            printf("\n");
        }
    }
    printf("]\n");


    free(constants);
    for (i = 0; i < k; i++){
        free(coefficientMatrix[i]);
    }
    free(coefficientMatrix);
    return 0;
}