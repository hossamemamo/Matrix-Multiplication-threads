#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define Item(X, I, J, NCOL)      X[((J) + (I) * (NCOL))]

extern void matmult(int* A, int* B, int* C, int l, int m, int n);
extern void matmult_v1(int* A, int* B, int* C, int l, int m, int n);
extern void matmult_v2(int* A, int* B, int* C, int l, int m, int n);
void populateMatrix(int *X, int nrow, int ncol);
void printMatrix(int *X, int nrow, int ncol);
int main()
{

    clock_t start, end;
    double execution_time1,execution_time2,execution_time3;



    int l=500, m=500, n=50;
    int *A = (int*)malloc(l*m*sizeof(int));
    int *B = (int*)malloc(m*n*sizeof(int));
    int *C = (int*)malloc(l*n*sizeof(int));

    populateMatrix(A, l, m);
    populateMatrix(B, m, n);


    printf("Matrix A\n");
    printMatrix(A, l, m);
    printf("Matrix B\n");
    printMatrix(B, m, n);



    start = clock();
    matmult_v1(A, B, C, l, m, n);
    end = clock();
    execution_time1 = ((double)(end - start))/CLOCKS_PER_SEC;
    
    printf("Matrix multiplication version 1\n");
    printMatrix(C, l, n);


    printf("matrix multiplication version 2\n");
    start = clock();
    matmult_v2(A, B, C, l, m, n);
    end = clock();
    execution_time2 = ((double)(end - start))/CLOCKS_PER_SEC;
    printMatrix(C, l, n);

    start = clock();
    matmult(A, B, C, l, m, n);
    end = clock();
    execution_time3 = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("matrix correct solution\n");
    printMatrix(C, l, n);

    printf("==============================================\n");
    printf("Time taken by calculating each element in the output matrix with a thread = %f seconds\n",execution_time1);
    printf("Time taken by calculating each row in the output matrix with a thread = %f seconds\n",execution_time2);
    printf("Time taken by calculating each output using normal nested loop = %f seconds\n",execution_time3);


    free(A);
    free(B);
    free(C);

    return 0;
}


/*
 * fill in a matrix with random numbers
 */
void populateMatrix(int *X, int nrow, int ncol)
{
    for(int i=0; i<nrow; i++)
        for(int j=0; j<ncol; j++)
            Item(X, i, j, ncol) = (((long)X)
                                + ((long)&nrow)
                                + ((long)&nrow)
                                - (~(i*ncol+nrow)
                                   +(j*nrow+ncol))
                                ) %29311%10;
}



/*
 * prints a matrix on stdout
 */
void printMatrix(int *X, int nrow, int ncol)
{
    for(int i=0; i<nrow; i++)
    {
        for(int j=0; j<ncol; j++)
            printf("%d\t", Item(X, i, j, ncol));
        printf("\n");
    }
    printf("\n");
    printf("\n");
}
