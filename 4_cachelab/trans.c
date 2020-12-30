/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        int bsize = 8;
        for (int i = 0; i < N; i += bsize)
            for (int j = 0; j < M; j += bsize)
                for (int x = i; x < i + bsize; x++)
                {
                    /* 先处理非对角线元素 */
                    for (int y = j; y < j + bsize; y++)
                        if (x != y)
                            B[y][x] = A[x][y];
                    /* 再处理对角线元素 */
                    if (i == j)
                        B[x][x] = A[x][x];
                }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */
char trans_block_desc[] = "block";
void trans_block(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        int bsize = 8;
        for (int i = 0; i < N; i += bsize)
        {
            for (int j = 0; j < M; j += bsize)
            {
                for (int x = i; x < i + bsize; x++)
                {
                    for (int y = j; y < j + bsize; y++)
                    {
                        B[y][x] = A[x][y];
                    }
                }
            }
        }
    }
}

char trans_reorder_desc[] = "block && reorder";
void trans_reorder(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        int bsize = 8;
        for (int i = 0; i < N; i += bsize)
            for (int j = 0; j < M; j += bsize)
                for (int x = i; x < i + bsize; x++)
                {
                    /* 先处理非对角线元素 */
                    for (int y = j; y < j + bsize; y++)
                        if (x != y)
                            B[y][x] = A[x][y];
                    /* 再处理对角线元素 */
                    if (i == j)
                        B[x][x] = A[x][x];
                }
    }
}

char trans_2step_desc[] = "block && copy && trans";
void trans_2step(int M, int N, int A[N][M], int B[M][N])
{
    if (M == 32 && N == 32)
    {
        int bsize = 8;
        int a0, a1, a2, a3, a4, a5, a6, a7;
        int tmp;
        for (int i = 0; i < N; i += bsize)
            for (int j = 0; j < M; j += bsize)
            {
                /* 分块矩阵直接复制到矩阵B（分块内部没有转置，但是位置是转置后的位置）*/
                for (int k = 0; k < bsize; k++)
                {
                    a0 = A[i + k][j];
                    a1 = A[i + k][j + 1];
                    a2 = A[i + k][j + 2];
                    a3 = A[i + k][j + 3];
                    a4 = A[i + k][j + 4];
                    a5 = A[i + k][j + 5];
                    a6 = A[i + k][j + 6];
                    a7 = A[i + k][j + 7];
                    B[j + k][i] = a0;
                    B[j + k][i + 1] = a1;
                    B[j + k][i + 2] = a2;
                    B[j + k][i + 3] = a3;
                    B[j + k][i + 4] = a4;
                    B[j + k][i + 5] = a5;
                    B[j + k][i + 6] = a6;
                    B[j + k][i + 7] = a7;
                }

                /* 分块矩阵内转置，不会造成冲突 */
                for (int x = 0; x < bsize - 1; x++)
                {
                    for (int y = x + 1; y < bsize; y++)
                    {
                        tmp = B[j + x][i + y];
                        B[j + x][i + y] = B[j + y][i + x];
                        B[j + y][i + x] = tmp;
                    }
                }
            }
    }
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    // registerTransFunction(trans_block, trans_block_desc);
    // registerTransFunction(trans_reorder, trans_reorder_desc);
    // registerTransFunction(trans_2step, trans_2step_desc);
    // registerTransFunction(trans, trans_desc);a
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; ++j)
        {
            if (A[i][j] != B[j][i])
            {
                return 0;
            }
        }
    }
    return 1;
}