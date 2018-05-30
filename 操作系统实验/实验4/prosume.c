#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

# define BUFFER_SIZE 10

int buffer[BUFFER_SIZE+1]; 
int front = 0, rear = 0; 
sem_t mutex, empty, full;

struct command {
    int id; 
    int num; 
    int runtime;
    int sleeptime;
};
 
int insertItem(int item) {
    if ((rear+1)%(BUFFER_SIZE+1) == front) 
        return -1;
    buffer[rear] = item;
    rear = (rear+1)%(BUFFER_SIZE+1);
    return 0;
}

int removeItem(int* item) {
    if (front == rear) 
        return -1;
    *item = buffer[front];
    front = (front+1) % (BUFFER_SIZE+1);
    return 0;
}

void* producer(void* param) {
    struct command data = *(struct command*)param;

    while(1) {
        sleep(data.sleeptime);
        sem_wait(&empty);
        sem_wait(&mutex);
        printf("producer %d produces products %d\n", data.id, data.num);
        if (insertItem(data.num))
            printf("Insert error\n");
        sleep(data.runtime);
        sem_post(&mutex);
        sem_post(&full);
        pthread_exit(0);
    }
}

void* consumer(void* param) {
    struct command data = *(struct command*)param;

    while(1) {
        sleep(data.runtime);
        sem_wait(&full);
        sem_wait(&mutex);
        if (removeItem(&data.num))
            printf("remove error\n");
        else
            printf("consumer %d consumes products %d \n", data.id, data.num);
        sleep(data.runtime);
        sem_post(&mutex);
        sem_post(&empty);
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
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    data = (struct command*)malloc((Thread_num+1)*sizeof(struct command));
    tid = (pthread_t*)malloc((Thread_num+1)*sizeof(pthread_t));
    attr = (pthread_attr_t*)malloc((Thread_num+1)*sizeof(pthread_attr_t));

    for (i = 0; i < Thread_num; i++) {
        pthread_attr_init(&attr[i]);
        scanf("%d", &data[i].id);
        getchar();
        char C;
        scanf("%c", &C);
        if (C == 'P') {
            scanf("%d", &(data[i].sleeptime));
            scanf("%d", &(data[i].runtime));
            scanf("%d", &(data[i].num));
            pthread_create(&tid[i], &attr[i], producer, &data[i]);
        } 
        else if (C == 'C') {
            scanf("%d", &(data[i].sleeptime));
            scanf("%d", &(data[i].runtime));
            pthread_create(&tid[i], &attr[i], consumer, &data[i]);
        }
    }
    sleep(100);

    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
