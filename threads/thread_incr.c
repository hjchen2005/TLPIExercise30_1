#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include "tlpi_hdr.h"
#include "thread_incr.h"

int main(int argc, char *argv[]) {
    pthread_t t1, t2;
    int loops, s;
    struct arguments newArgument1;
    struct arguments newArgument2;
    //newArgument1.loops = newArgument2.loops (argc > 1) ? getInt(argv[1], GN_GT_0, "num-loops") : 10000000;

    s = pthread_create(&t1, NULL, threadFunc, &newArgument1);
    if (s != 0)
        errExitEN(s, "pthread_create");
    s = pthread_create(&t2, NULL, threadFunc, &newArgument2);
    if (s != 0)
        errExitEN(s, "pthread_create");

    s = pthread_join(t1, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");
    s = pthread_join(t2, NULL);
    if (s != 0)
        errExitEN(s, "pthread_join");

    //printf("glob = %d\n", glob);
    FILE *fp = fopen("glob.txt", "ab+");
    if(!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }
    //fwrite(buffer, sizeof(char), sizeof(buffer), fp);
    fprint(fp,"The value of glob is ",glob);
    fclose(fp);
    exit(EXIT_SUCCESS);
}
