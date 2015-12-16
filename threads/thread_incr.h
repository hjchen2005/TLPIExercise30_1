#ifndef THREAD_INCR_H
#define THREAD_INCR_H

struct arguments {
    int loops;
    pthread_t self;
};

static void * threadFunc(void *arg);
void printPt(pthread_t pt);
static volatile int glob = 0;   /* "volatile" prevents compiler optimizations
                                   of arithmetic operations on 'glob' */
static void * threadFunc(void *arg){
    struct arguments * threadFuncArgs = arg;
    int threadFuncLoops = threadFuncArgs->loops;
	threadFuncArgs->self = pthread_self();
	printPt(threadFuncArgs->self);
    int loc, j;
	printf("\n glob = %d\n", glob);
    for (j = 0; j < threadFuncLoops; j++) {
        loc = glob;
        loc++;
        glob = loc;
    }
	printf("\n now glob = %d\n", glob);
    return NULL;
}

void printPt(pthread_t pt) {
  unsigned char *ptc = (unsigned char*)(void*)(&pt);
  //printf(f, "0x");
  for (size_t i=0; i<sizeof(pt); i++) {
    printf("%02x", (unsigned)(ptc[i]));
  }
}

#endif
