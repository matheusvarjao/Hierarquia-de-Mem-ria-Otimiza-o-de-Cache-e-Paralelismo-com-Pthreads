#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <N>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    double *mat = (double *)malloc((size_t)N * N * sizeof(double));
    
    // Inicialização
    for (int i = 0; i < N * N; i++) mat[i] = 1.0;

    clock_t inicio = clock();
    double soma = 0.0;

    // Varredura por coluna (acesso não-sequencial / saltos)
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            soma += mat[i * N + j];
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("[Varredura Coluna] N: %d | Pares: %d | Tempo: %.4f s\n", N, N * N, tempo);
    free(mat);
    return 0;
}