#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t readcount, wrt, mutex;

struct command {
    int id;
    int runtime;
    int sleeptime;
};

void* writer(void* param) {
    struct command data = *(struct command*)param;

    while(1) {
        sleep(data.sleeptime);
        sem_wait(&wrt);
        printf("Writer %d starts writing!\n", data.id);
        sleep(data.runtime);
        printf("Writer %d ends writing!\n", data.id);
        sem_post(&wrt);
        pthread_exit(0);
    }
}

void* reader(void* param) {
    struct command data = *(struct command*)param;

    while(1) {
        sleep(data.sleeptime);
        sem_wait(&mutex);

        int value;
        sem_getvalue(&readcount, &value);
        sem_init(&readcount, 0, value+1);
        sem_getvalue(&readcount, &value);
        if (value == 1)
            sem_wait(&wrt);
        sem_post(&mutex);
        printf("Reader %d starts reading!\n", data.id);
        sleep(data.runtime);
        printf("Reader %d ends reading!\n", data.id);
        sem_wait(&mutex);
        sem_getvalue(&readcount, &value);
        sem_init(&readcount, 0, value-1);
        sem_getvalue(&readcount, &value);
        if (value == 0)
            sem_post(&wrt);
        sem_post(&mutex);
        pthread_exit(0);
    }
}

int main(int argc, char* argv[]) {
    int Thread_num, i;
    if (argc != 2) {
        fprintf(stderr, "usage:./a.out <integer value>\n");
        return -1;
    } 
    else {
        Thread_num = atoi(argv[1]);
    }
    struct command* data;
    pthread_t* tid;
    pthread_attr_t* attr;
    sem_init(&mutex, 0, 1);
    sem_init(&readcount, 0, 0);
    sem_init(&wrt, 0, 1);
    data = (struct command*)malloc((Thread_num+1)*sizeof(struct command));
    tid = (pthread_t*)malloc((Thread_num+1)*sizeof(pthread_t));
    attr = (pthread_attr_t*)malloc((Thread_num+1)*sizeof(pthread_attr_t));

    for (i = 0; i < Thread_num; i++) {
        pthread_attr_init(&attr[i]);
        scanf("%d", &data[i].id);
        getchar();
        char C;
        scanf("%c", &C);
        if (C == 'R') {
            scanf("%d", &(data[i].sleeptime));
            scanf("%d", &(data[i].runtime));
            pthread_create(&tid[i], &attr[i], reader, &data[i]);
        } 
        else if (C == 'W') {
            scanf("%d", &(data[i].sleeptime));
            scanf("%d", &(data[i].runtime));
            pthread_create(&tid[i], &attr[i], writer, &data[i]);
        }
    }
    sleep(100);

    sem_destroy(&mutex);
    sem_destroy(&readcount);
    sem_destroy(&wrt);

    return 0;
}
