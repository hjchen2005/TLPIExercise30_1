//After the main thread terminates, threadFunc() will continue working with storage 
//on the main thread’s stack, with unpredictable results.
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>

struct SomeStruct {
    int num;
};

static void * threadFunc(void *arg){
    // orignial code:
    //struct someStruct *pbuf = (struct someStruct *) arg;
    struct SomeStruct *pbuf = arg;
    /* Do some work with structure pointed to by 'pbuf' */
    arg->num = 10;
    printf("number in the structure: ",arg->num);
}

int main(int argc, char *argv[]) {
    struct SomeStruct buf;

    pthread_t thr;
    int s;
    s = pthread_create(&thr, NULL, threadFunc, (void *) &buf);
    if (s!=0)
        printf("thread creation failed \n");
    pthread_exit(NULL);

    return 0;
}
