#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define M 1000
#define N 1000
#define P 1000

int main() {
    int i, j, k;
    int *matrix1 = (int *)malloc(M * N * sizeof(int));
    int *matrix2 = (int *)malloc(N * P * sizeof(int));
    int *result = (int *)calloc(M * P, sizeof(int));

    // Initialize matrices with random values
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            *(matrix1 + i * N + j) = rand() % 10;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            *(matrix2 + i * P + j) = rand() % 10;
        }
    }

    double start_time = omp_get_wtime();

    // Matrix multiplication using OpenMP
    #pragma omp parallel for private(i,j,k) shared(matrix1, matrix2, result)
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            for (k = 0; k < N; k++) {
                *(result + i * P + j) += *(matrix1 + i * N + k) * *(matrix2 + k * P + j);
            }
        }
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    // Print the result matrix
    printf("The result matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", *(result + i * P + j));
        }
        printf("\n");
    }

    printf("Elapsed time: %lf seconds\n", elapsed_time);

    // Free memory allocated for matrices
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}
