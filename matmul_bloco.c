#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <N> <Bloco>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int B = atoi(argv[2]);

    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    double *B_mat = (double *)malloc((size_t)N * N * sizeof(double));
    double *C = (double *)calloc((size_t)N * N, sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B_mat[i] = 1.0;
    }

    clock_t inicio = clock();

    // Multiplicação de Matrizes com Blocagem (Tiling)
    for (int sj = 0; sj < N; sj += B) {
        for (int sk = 0; sk < N; sk += B) {
            for (int si = 0; si < N; si += B) {
                // Bloco interno
                for (int i = si; i < si + B && i < N; i++) {
                    for (int k = sk; k < sk + B && k < N; k++) {
                        for (int j = sj; j < sj + B && j < N; j++) {
                            C[i * N + j] += A[i * N + k] * B_mat[k * N + j];
                        }
                    }
                }
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("[Matmul Blocado] N: %d, Bloco: %d | Tempo: %.4f s\n", N, B, tempo);

    free(A); free(B_mat); free(C);
    return 0;
}