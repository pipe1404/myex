#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#define NUMTHREAD 10


void* say_hello(void* pos)
{
    printf("Hello from thread %d \n", pos);
}

int main(int argc, char* argv[])
{
    pthread_t* tid = malloc(NUMTHREAD* sizeof(pthread_t));
    pthread_attr_t* attr = malloc(NUMTHREAD* sizeof(pthread_attr_t));

    for (size_t i = 0; i < NUMTHREAD; i++)
    {
        pthread_attr_init(attr+i);
        pthread_create(&tid[i], &attr[i], say_hello, (void*) i);
        pthread_join(tid[i], NULL);
    }
    
    free(tid);
    free(attr);
    pthread_exit(0); 
}