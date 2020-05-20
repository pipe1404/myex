#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h> 

#define RADIUS 1
#define NUMBER_OF_THREADS 8

time_t start = 0;

size_t S, C;
pthread_mutex_t lock, mylock_genpoint;

typedef struct point
{
    double x;
    double y;
} point, *ppoint;


point genpoint(unsigned int *myseed)
{
    point p;

    //       0 <=           ran#        <= 1
    //       0 <=       ran#*2RADIUS    <= 2RADIUS
    // -RADIUS <= ran#*2RADIUS - RADIUS <= RADIUS

    p.x = ((double)rand_r(myseed) / RAND_MAX)*2*RADIUS - RADIUS;
    p.y = ((double)rand_r(myseed) / RAND_MAX)*2*RADIUS - RADIUS;

    // pthread_mutex_lock(&mylock_genpoint);
    //     srand(time(0));
    //     p.x = ((double)rand() / RAND_MAX)*2*RADIUS - RADIUS;
    //     p.y = ((double)rand() / RAND_MAX)*2*RADIUS - RADIUS;
    // pthread_mutex_unlock(&mylock_genpoint);

    return p;
}
int isInsideCircle(ppoint p)
{
    return (p->x*p->x + p->y*p->y <= RADIUS*RADIUS);
}

void* mymethod(void* ncount)
{
    size_t mS, mC;
    mS = 0;
    mC = 0;

    unsigned int myseed = time(0) + pthread_self();
    for (size_t i = 0; i < (size_t)ncount; i++)
    {
        point p = genpoint(&myseed);   
        mS++;
        isInsideCircle(&p) ? mC++ : 0;
    }

    pthread_mutex_lock(&lock);
        S += mS;
        C += mC;
    pthread_mutex_unlock(&lock);
    
    pthread_exit(0);
}

int main(int argc, char** argv)
{
    start = clock();

    if( argc != 2) 
    {
        fprintf ( stderr , "usage : ./pi_multi-thread␣<integer␣value>\n" );
        return -1;
    }
    if(atoi(argv[1]) < 0) 
    {
        fprintf ( stderr,"%d␣must␣be␣>=␣0\n" ,atoi(argv[1])) ;
        return -1;
    }
    size_t count = atoi(argv[1]);

    S = 0;
    C = 0;

    pthread_mutex_init(&lock, NULL);
    // pthread_mutex_init(&mylock_genpoint, NULL);
    pthread_t* tid = malloc(NUMBER_OF_THREADS * sizeof(pthread_t));
    size_t count_per_thread = count / NUMBER_OF_THREADS;

    for (size_t i = 0; i < NUMBER_OF_THREADS; i++)
    {
        if (i == NUMBER_OF_THREADS - 1)
        {   
            pthread_create(&tid[i], NULL,mymethod, (void*)count);
        }
        else
        {
            pthread_create(&tid[i], NULL,mymethod, (void*)count_per_thread);
            count -= count_per_thread;
        }
    }
    for (size_t i = 0; i < NUMBER_OF_THREADS; i++)
    {
        pthread_join(tid[i], NULL);
    }    
    pthread_mutex_destroy(&lock);

    double calc_pi = 4.0*C / S; 
    printf("%f", calc_pi);  
}
