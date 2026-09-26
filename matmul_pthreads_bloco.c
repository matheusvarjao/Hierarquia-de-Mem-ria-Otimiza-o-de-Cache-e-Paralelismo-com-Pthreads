#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int id;
    int N;
    int B;
    int num_threads;
    double *A;
    double *B_mat;
    double *C;
} ThreadArgs;

void *worker(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int N = args->N;
    int B = args->B;
    int id = args->id;
    int num_threads = args->num_threads;

    int linhas_por_thread = N / num_threads;
    int inicio_i = id * linhas_por_thread;
    int fim_i = (id == num_threads - 1) ? N : inicio_i + linhas_por_thread;

    for (int sj = 0; sj < N; sj += B) {
        for (int sk = 0; sk < N; sk += B) {
            for (int si = inicio_i; si < fim_i; si += B) {
                int lim_i = (si + B < fim_i) ? si + B : fim_i;
                for (int i = si; i < lim_i; i++) {
                    for (int k = sk; k < sk + B && k < N; k++) {
                        for (int j = sj; j < sj + B && j < N; j++) {
                            args->C[i * N + j] += args->A[i * N + k] * args->B_mat[k * N + j];
                        }
                    }
                }
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <N> <Bloco> <Threads>\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[1]);
    int B = atoi(argv[2]);
    int num_threads = atoi(argv[3]);

    double *A = (double *)malloc((size_t)N * N * sizeof(double));
    double *B_mat = (double *)malloc((size_t)N * N * sizeof(double));
    double *C = (double *)calloc((size_t)N * N, sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = 1.0;
        B_mat[i] = 1.0;
    }

    pthread_t *threads = malloc(num_threads * sizeof(pthread_t));
    ThreadArgs *args = malloc(num_threads * sizeof(ThreadArgs));

    clock_t inicio = clock();

    for (int t = 0; t < num_threads; t++) {
        args[t].id = t;
        args[t].N = N;
        args[t].B = B;
        args[t].num_threads = num_threads;
        args[t].A = A;
        args[t].B_mat = B_mat;
        args[t].C = C;
        pthread_create(&threads[t], NULL, worker, (void *)&args[t]);
    }

    for (int t = 0; t < num_threads; t++) {
        pthread_join(threads[t], NULL);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("[Matmul Pthreads+Bloco] N: %d, Bloco: %d, Threads: %d | Tempo: %.4f s\n", N, B, num_threads, tempo);

    free(A); free(B_mat); free(C);
    free(threads); free(args);
    return 0;
}