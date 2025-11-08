#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    double start, end;
    const int count = 10000000;
    const int random_seed = 920214;
    const int target = 16;
    const int threads = 4;

    int* array = 0;
    int  index = count;

    srand(random_seed);

    array = (int*) malloc(count*sizeof(int));
    for(int i = 0; i < count; i++) { array[i] = rand(); }

    start = omp_get_wtime();
    #pragma omp parallel num_threads(threads) shared(array, target, count) reduction(min: index) default(none)
    {
        unsigned int flag = 0;
        #pragma omp for
        for(int i = 0; i < count; i++)
        {
            if(array[i] == target && !flag) {
                index = i;
                flag = 1;
            }
        }
    }
    if (index == count)
        index = -1;
    end = omp_get_wtime();

    printf("Found occurence of %d at index %d;\nTime: %f\n", target, index, end - start);
    return 0;
}