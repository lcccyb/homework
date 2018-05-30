#include <stdio.h>
#include <pthread.h>

// the size of fibonacci array
int n;

void *fibonacci(void *data) {
    int *a = (int*)data;
    // calculate the fibonacci array
    for (int i = 2; i < n; i++) {
        a[i] = a[i-1] + a[i-2];
    }
    pthread_exit(0);
}

int main() {
    //the fibonacci array
    int a[1000];
    printf("Please enter the number: ");
    scanf("%d", &n);
    //error when input is out of range
    if(n < 0 || n > 1000) {
        printf("input error!\n");
        return -1;
    }
    // initial a[0] and a[1]
    a[0] = 0;
    a[1] = 1;
    //TID
    pthread_t th;
    // create a thread to calculate
    ret = pthread_create(&th, NULL, fibonacci, (void*)a);
    if( ret != 0 ){
        printf("Create thread error!\n");
        return -1;
    }
    // a thread to be joined upon
    pthread_join(th, NULL);

    printf("Result: ");
    // output the result
    if(n == 0) {
        printf("No output!\n");
    }
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}
