#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define NUM_THREAD 3
int average, min, max;
void *
doSomeThing(void *param)
{
    int *argv = (int *) param;
    sleep(1);
int j;
    int sum = 0;
    int upper = atoi(param);

    sleep(1);
    pthread_t id = pthread_self();
     unsigned long i = 0;
      if (id = 1) {
        int i;
 for (i = 0; i < upper; i++) {
            sum += argv[i];
        }
        printf("sum of no's is :\n", sum);
    }
    if (id = 2) {
        printf("\n Second thread processing\n");
    }
    if (id = 3) {
        printf("\n Third thread processing\n");
    }

    for (i = 0; i < -1; i++);
    {
        pthread_exit(NULL);
    }
}
int
main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREAD];
    pthread_attr_t attr;
    int *taskid[NUM_THREAD];
    int i = 0;
    int t;
    int err;
    //int input,a;
    if (argc != 2) {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
}
 pthread_attr_init(&attr);
    for (t = 0; t < NUM_THREAD; t++) {
        taskid[t] = (int *) malloc(sizeof(int));
        *taskid[t] = t;
        printf("In main: creating thread %d\n", t);
        err = pthread_create(&threads[t], &attr, doSomeThing, argv[1]);

        if (err) {
            printf("Error; return code from pthread_create() is %d\n",
                   err);
            exit(-1);
  }
    }
    for (t = 0; t < NUM_THREAD; t++) {
        pthread_join(threads[t], NULL);
        printf("Joining thread %d\n", t);
    }
    pthread_exit(NULL);
}