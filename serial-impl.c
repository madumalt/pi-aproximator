/* Serial Algorithm to compute Pi using Monte Carlo method. */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define BILLION 1E9
#define NO_OF_ITERATIONS  1000*1000*1000

/**
Calculate the elapsed time from the given start and end time.
**/
double get_elapsed_time(struct timespec requestStart, struct timespec requestEnd) {
    return (requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
}

/**
Estimate Pi from given in_count and N.
**/
double estimate_Pi(long in_count, long N) {
    return (double)in_count / N*4;
}

/**
Checks whether the given x,y is inside unit circle or not.
**/
bool is_inside_unit_circle(double x, double y) {
    return sqrt( x*x + y*y ) <= 1;
}

int main (int argc, char* argv) {

    struct timespec requestStart, requestEnd;
    // Record the starting time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestStart);

    // Initialize random numbers.
    srand(time(NULL));
    // Estimate Pi.
    long count = 0;
    for ( long i = 0; i < NO_OF_ITERATIONS; i++) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        bool is_inside = is_inside_unit_circle(x, y);
        if (is_inside) count++;
        // printf("%d, x: %f, y: %f, is_inside: %s \n", count, x, y, is_inside ? "true" : "false");
    }
    double pi = estimate_Pi(count, NO_OF_ITERATIONS);

    // Record finishing time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestEnd);
    // Calculates the elapsed time.
    double elapsed_time = get_elapsed_time(requestStart, requestEnd);

    printf("No of trials: %d , estimate of Pi: %g, elapsed time: %1f\n", NO_OF_ITERATIONS, pi, elapsed_time);
}
