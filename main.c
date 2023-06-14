#define STOPWATCH_IMPLEMENTATION
#include "stopwatch.h"
#include <stdio.h>

int main(void)
{
    Stopwatch sw = sw_create_and_start();

    for (int i = 0; i < 10; i++) {
        printf("Iteration %d\n", i);
        Sleep(100);
    }

    sw_stop(&sw);

    printf("Elapsed time: %.3fms\n", sw.elapsed_milliseconds);

    return 0;
}
