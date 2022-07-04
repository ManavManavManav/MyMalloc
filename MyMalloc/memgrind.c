#include <stdlib.h>
#include "mymalloc.h"
#include <sys/time.h>
#include <time.h>

int test1()
{

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for (int i = 0; i < 120; i++)
    {
        char *x = malloc(1);
        free(x);
    }

    gettimeofday(&stop, NULL);

    return (int)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}
int test2()
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    char *array[120];
    for (int i = 0; i < 120; i++)
    {
        array[i] = malloc(1);
    }
    for (int i = 0; i < 120; i++)
    {
        free(array[i]);
    }

    gettimeofday(&stop, NULL);

    return (int)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}
int test3()
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    int ops = 0;
    int ptrs = 0;
    char *array[120];
    int radm = 0;

    while (ops < 120)
    {
        radm = rand();

        if (radm % 2 == 0)
        {
            array[ptrs] = malloc(1);
            ops++;
            ptrs++;
        }
        else
        {
            if (ptrs > 0)
            {
                free(array[ptrs - 1]);
                ptrs--;
            }
        }
    }
    while (ptrs > 0)
    {
        free(array[ptrs - 1]);
        ptrs--;
    }

    gettimeofday(&stop, NULL);
    return (int)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}

int test4()
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    for (int i = 0; i < 120; i++)
    {
        char *a = malloc(1000);
        char *b = malloc(1000);
        char *c = malloc(1000);
        free(a);
        free(c);
        free(b);

        char *z = malloc(3000 - 24);
        free(z);
    }

    gettimeofday(&stop, NULL);

    return (int)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}

int test5()
{
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    int r=26;
    char **array=malloc(r*sizeof(char*));
    //8*r
    for(int i=0;i<r;i++){
        array[i]=malloc(120*sizeof(char));
        //(x+24)*r
        //4096>=(152r)
        //if 120 cols then 26 max rows
    }
    for(int i=0;i<r;i++){
        free(array[i]);
    }
    free(array);


    gettimeofday(&stop, NULL);
    return (int)((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
}

int main()
{
    int sum = 0;

    sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += test1();
    }
    sum /= 50;
    printf("Test1: %d microseconds\n", sum);




    sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += test2();
    }
    sum /= 50;
    printf("Test2: %d microseconds\n", sum);





    sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += test3();
    }
    sum /= 50;
    printf("Test3: %d microseconds\n", sum);






    sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += test4();
    }
    sum /= 50;
    printf("Test4: %d microseconds\n", sum);






    sum = 0;
    for (int i = 0; i < 50; i++)
    {
        sum += test5();
    }
    sum /= 50;
    printf("Test5: %d microseconds\n", sum);
}