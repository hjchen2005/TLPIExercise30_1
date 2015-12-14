#include <pthread>
#include <sys/types.h>
#include <stdio.h>

struct SomeStruct {
    int num = 0;
};

static void * threadFunc(void *arg){
    // orignial code:
    //struct someStruct *pbuf = (struct someStruct *) arg;
    struct someStruct *pbuf = arg;
    /* Do some work with structure pointed to by 'pbuf' */
    pbuf->num++;
    printf("number in the structure: ",num);
}

int main(int argc, char *argv[]) {
    struct someStruct buf;
    pthread_t thr;
    int s;
    s = pthread_create(&thr, NULL, threadFunc, (void *) &buf);
    if (s!=0)
        printf("thread creation failed \n");
    pthread_exit(NULL);
    return 0;
}
