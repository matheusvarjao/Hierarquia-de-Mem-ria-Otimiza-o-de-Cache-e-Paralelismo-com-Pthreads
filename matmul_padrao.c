#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <N>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    double *B = (double *)malloc((size_t)N * N * sizeof(double));
    double *C = (double *)calloc((size_t)N * N, sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B[i] = 1.0;
    }

    clock_t inicio = clock();

    // Multiplicação de Matrizes Canónica O(N^3)
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("[Matmul Padrao] N: %d | Tempo: %.4f s\n", N, tempo);

    free(A); free(B); free(C);
    return 0;
}