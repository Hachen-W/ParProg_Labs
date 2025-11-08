#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    double start, end;
    double time;
    const int count = 10000000;
    const int threads = 4;
    const int random_seed = 920215;

    int* array = 0;
    int  max   = -1;
    unsigned int compare_count = 0;

    srand(random_seed);

    array = (int*)malloc(count*sizeof(int));
    for(int i=0; i<count; i++) { array[i] = rand(); }

    start = omp_get_wtime();
    #pragma omp parallel num_threads(threads) shared(array, count) reduction(max: max) default(none)
    {
        #pragma omp for
        for(int i=0; i<count; i++)
        {
            if(array[i] > max) { max = array[i]; };
        }
    }
    end = omp_get_wtime();
    printf("======\nMax is: %d; Time is: %.6f\n,", max, end - start);
    return 0;
}