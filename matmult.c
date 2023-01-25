#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#define Item(X, I, J, NCOL) X[((J) + (I) * (NCOL))]

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

// DEFINING GLOBAL A ,B,C
int *A_p;
int *B_p;
int *C_p;
long long MAX_THREADS_V2;
long long MAX_THREADS_V1;
int l_global;
int m_global;
int n_global;
void matmult(int *A, int *B, int *C, int l, int m, int n)
{
    for (int i = 0; i < l; i++)
        for (int j = 0; j < n; j++)
        {
            int sum = 0;
            for (int k = 0; k < m; k++)
                sum += Item(A, i, k, m) * Item(B, k, j, n);
            Item(C, i, j, n) = sum;
        }
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */

void *matmult_v1_helper(void *arg)
{
    long long * iptr = (long long *)arg;
    long long temp=*iptr;
    long long row = (int)(temp / n_global); // i
    long long col = temp % n_global; // j

    long long sum = 0;
    for (int k = 0; k < m_global; k++)
    {

        sum += Item(A_p, row, k, m_global) * Item(B_p, k, col, n_global);
    }
    Item(C_p, row, col, n_global) = sum;
    pthread_exit(NULL);
}
void matmult_v1(int *A, int *B, int *C, int l, int m, int n)
{

    A_p = A;
    B_p = B;
    C_p = C;
    l_global = l;
    m_global = m;
    n_global = n;
    MAX_THREADS_V1 = l * n;
    pthread_t threadsArr[MAX_THREADS_V1]; // number or rows is the number of threads
    for (long long i = 0; i < MAX_THREADS_V1; i++)
    {
    	long long * index= malloc(sizeof(long long));
        *index=i;
        pthread_create(&threadsArr[i], NULL, matmult_v1_helper, (void *)index);
    }

    for (long long i = 0; i < MAX_THREADS_V1; i++)
        pthread_join(threadsArr[i], NULL);
}

/*
 * matrix multiplication
 *     C = A*B
 *     A has l rows and m cols
 *     B has m rows and n cols
 *     C has l rows and n cols
 */
void *matmult_v2_helper(void *arg)
{
    long long * iptr = (long long *)arg;
    long long temp = *iptr;
    for (long long j = 0; j < n_global; j++)
    {
        long long sum = 0;
        for (long long k = 0; k < m_global; k++)
        {
            sum += Item(A_p, temp, k, m_global) * Item(B_p, k, j, n_global);
        }
        Item(C_p, temp, j, n_global) = sum;
    }
        pthread_exit(NULL);
}
void matmult_v2(int *A, int *B, int *C, int l, int m, int n)
{
    A_p = A;
    B_p = B;
    C_p = C;
    l_global = l;
    m_global = m;
    n_global = n;
    MAX_THREADS_V2 = l;
    pthread_t threadsArr[MAX_THREADS_V2]; // number or rows is the number of threads
    for (long long i = 0; i < MAX_THREADS_V2; i++)
    {
    	long long * index= malloc(sizeof(long long));
        *index=i;
        pthread_create(&threadsArr[i], NULL, matmult_v2_helper, (void *)index);
    }

    for (long long i = 0; i < MAX_THREADS_V2; i++)
        pthread_join(threadsArr[i], NULL);
}
