#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h> 

#define RADIUS 1

time_t start;
size_t s, c;

typedef struct point
{
    double x;
    double y;
} point, *ppoint;

point genpoint()
{
    point p;

    //       0 <=           ran#        <= 1
    //       0 <=       ran#*2RADIUS    <= 2RADIUS
    // -RADIUS <= ran#*2RADIUS - RADIUS <= RADIUS
    p.x = ((double)rand() / RAND_MAX)*2*RADIUS - RADIUS;
    p.y = ((double)rand() / RAND_MAX)*2*RADIUS - RADIUS;

    return p;
}
int isInsideCircle(ppoint p)
{
    return (p->x*p->x + p->y*p->y <= RADIUS*RADIUS);
}

void serial_method(size_t ncount)
{
    for (size_t i = 0; i < ncount; i++)
    {
        point p = genpoint();
        s++;
        isInsideCircle(&p) ? c++ : 0;
    }
}

int main(int argc, char** argv)
{
    start = clock();
    if( argc != 2) 
    {
        fprintf ( stderr , "usage : ./pi_serial␣<integer␣value>\n" );
        return -1;
    }
    if(atoi(argv[1]) < 0) 
    {
        fprintf ( stderr,"%d␣must␣be␣>=␣0\n" ,atoi(argv[1])) ;
        return -1;
    }
    size_t count = atoi(argv[1]);

    s = 0;
    c = 0;
    
    serial_method(count);
    double calc_pi = 4.0*c / s; 

    printf("%f", calc_pi);
}
