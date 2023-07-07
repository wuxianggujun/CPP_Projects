/**
* Created by WuXiangGuJun on 2023/4/7.
*/
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *threadfunc(void *arg) {
    while (1) {
        sleep(1);
        printf("I am a New Thread!\n");
    }
    return NULL;
}

int main() {
    pthread_t threadid;
    pthread_create(&threadid, NULL, threadfunc, NULL);
    while (1) {

    }
    return 0;
}
