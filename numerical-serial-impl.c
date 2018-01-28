#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BILLION 1E9
#define NO_OF_ITERATIONS 1000*1000*1000

/**
Calculate the elapsed time from the given start and end time.
**/
double get_elapsed_time(struct timespec requestStart, struct timespec requestEnd) {
    return (requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
}

int main(void) {
    long num_rects = NO_OF_ITERATIONS;
    double mid, height, width, area;
    double sum = 0.0;
    struct timespec requestStart, requestEnd;

    // Record the starting time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestStart);

    width = 1.0 / (double) num_rects;
    for (long i = 0; i < num_rects; i++) {
        mid = (i + 0.5) * width;
        height = 4.0 / (1.0 + mid * mid);
        sum += height;
    }
    area = width * sum;

    // Record finishing time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    // Calculates the elapsed time.
    double elapsed_time = get_elapsed_time(requestStart, requestEnd);

    printf("No of trials: %d , estimate of Pi: %g, elapsed time: %1f\n", NO_OF_ITERATIONS, area, elapsed_time);
    return 0;
}
