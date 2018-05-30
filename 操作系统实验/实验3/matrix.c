#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int M, K, N;
// the maxsize of matrix
int A[200][200];
int B[200][200];
int C[200][200];
// structure for passing data to threads
struct Data {
    int i;
    int j;
};
// calculate the matrix product in C[row][col]
void *calculate(void *data) {
    struct Data *a = (struct Data*)data;
    int i = a->i;
    int j = a->j;
    for (int k = 0; k < K; k++) {
        C[i][j] += A[i][k] * B[k][j];
    }
    pthread_exit(0);
}

int main() {
    printf("Please enter three numbers(M/K/N): ");
    scanf("%d%d%d", &M, &K, &N);
    if(M > 200 || K > 200 || N > 200 || M < 0 || K < 0 || N < 0) {
        printf("input error\n");
        return -1;
    }
    printf("Please enter the first matrix: ");
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < K; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Please enter the second matrix: ");
    for(int i = 0; i < K; i++) {
        for(int j = 0; j < N; j++) {
            scanf("%d", & B[i][j]);
        }
    }
    //initailize matrix C
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            C[i][j] = 0;
        }
    }
    pthread_t tid[M*N];
    pthread_attr_t attr;
    // get the default attributes
    pthread_attr_init(&attr);
    //create M*N pthreads
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            struct Data *a = (struct Data*)malloc(sizeof(struct Data));
            a->i = i;
            a->j = j;
            int ret = pthread_create(&tid[i*N+j], &attr, calculate, (void*)a);
            if(ret != 0){
                printf("Create thread error!\n");
                return -1;
            }
        }
    }
    // join upon each thread
    for (int i = 0; i < M*N; i++) {
        pthread_join(tid[i], NULL);
    }
    // output the result
    printf("The result is:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", C[i][j]);
            if (j == N-1) {
                printf("\n");
            }
        }
    }
    return 0;
}