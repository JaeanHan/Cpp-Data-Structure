#include <stdio.h>
#include <stdlib.h>
#include "time.h"

#define AROWS 3
#define ACOLS 4
#define BROWS 4
#define BCOLS 5
#define CROWS 3
#define CCOLS 5

static unsigned long int next = 1;

int rand1(void)
{
    // printf("rand1()::next = %ld\n", next);
    next = next * 1103515245 + 12345;
    return (unsigned int)(next / 65536) % 32768;
}

void srand1(unsigned int seed)
{
    next = seed;
}

// pointer to array
int get_data(int (*p)[ACOLS], int n)
{
    for (int i = 0; i < ACOLS; i++)
        for (int j = 0; j < n; j++)
        {
            p[i][j] = rand1() % (n * n);
            // printf("%d, %d, %d\n", i, j, p[i][j]);
            // printf("\n");
        }

    return 1;
}

int get_data2(int (*p)[BCOLS], int n)
{
    for (int i = 0; i < BCOLS; i++)
        for (int j = 0; j < n; j++)
        {
            // printf("%d, %d\n", i, j);
            p[i][j] = rand1() % (n * n);
        }

    return 1;
}

int show_data(int (*p)[ACOLS], int n)
{
    for (int i = 0; i < ACOLS; i++)
    {
        for (int j = 0; j < n; j++)
            printf("p[%d][%d] : %d %s", i, j, p[i][j], (j + 1 == n ? " " : "| "));

        printf("\n");
    }
}

int show_data2(int (*p)[BCOLS], int n)
{
    for (int i = 0; i < BCOLS; i++)
    {
        for (int j = 0; j < n; j++)
            printf("p[%d][%d] : %d %s", i, j, p[i][j], (j + 1 == n ? " " : "| "));

        printf("\n");
    }
}

void multiply(int matrixA[][ACOLS], int ar, int matrixB[][BCOLS], int br, int matrixC[][CCOLS], int cr)
{
    for (int i = 0; i < BCOLS; i++)
        for (int j = 0; j < cr; j++)
        {
            matrixC[i][j] = 0;

            for (int k = 0; k < ACOLS; k++)
            {
                matrixC[i][j] += matrixA[i][k] * matrixB[j][k];
                // printf("a(%d,%d) : %d and b(%d,%d) : %d and c(%d, %d) : %d\n", i, k, matrixA[i][k], k, j, matrixB[k][j], i, j, matrixC[i][j]);
            }
        }
}

int main(void)
{
    int matrixA[AROWS][ACOLS];
    int matrixB[BROWS][BCOLS];
    int matrixC[CROWS][CCOLS];

    srand(time(NULL));

    printf("\nmatrixA : \n");
    get_data(matrixA, AROWS);
    show_data(matrixA, AROWS);

    printf("\nmatrixB : \n");
    get_data2(matrixB, BROWS);
    show_data2(matrixB, BROWS);

    printf("\nmatrixC : \n");
    multiply(matrixA, AROWS, matrixB, BROWS, matrixC, CROWS);
    show_data2(matrixC, AROWS);

    return 0;
}