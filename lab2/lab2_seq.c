#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv)
{
    double start, end;
    const int count = 10000000;
    const int random_seed = 920214;
    const int target = 16;

    int* array = 0;
    int  index = -1;

    srand(random_seed);

    array = (int*) malloc(count*sizeof(int));
    for(int i = 0; i < count; i++) { array[i] = rand(); }

    start = omp_get_wtime();
    for(int i = 0; i < count; i++)
    {
        if(array[i] == target)
        {
            index = i;
            break;
        }
    }
    end = omp_get_wtime();

    printf("Found occurence of %d at index %d;\nTime: %f\n", target, index, end - start);
    return 0;
}