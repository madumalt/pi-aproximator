#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define BILLION 1E9
#define NO_OF_ITERATIONS  1000*1000*1000

double pi;
long in_circle;
int no_of_threads;
pthread_mutex_t mutex;

/**
Calculate the elapsed time from the given start and end time.
**/
double get_elapsed_time(struct timespec requestStart, struct timespec requestEnd) {
    return (requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;
}

/**
Estimate Pi from given in_count and N.
**/
float estimate_pi(long in_count, long N) {
    return in_count / (double)N*4;
}

/**
Checks whether the given x,y is inside unit circle or not.
**/
bool is_inside_unit_circle(double x, double y) {
    return sqrt( x*x + y*y ) <= 1;
}

/**
Calculate the # of points inside the unit circle.
**/
long my_in_counter(long no_of_iteration) {

    unsigned int seed = 0;

    // Initialize random numbers.
    srand(time(NULL));
    long in_count = 0;
    long counter = 0;
    for (counter = 0 ; counter < no_of_iteration ; counter++) {
        double x = (double) rand_r(&seed) / RAND_MAX;
        double y = (double) rand_r(&seed) / RAND_MAX;
        bool is_inside = is_inside_unit_circle(x, y);
        if (is_inside) in_count++;
   }

   return in_count;
}

void *runner (void* arg) {
    long itrs_per_thread = NO_OF_ITERATIONS / no_of_threads;
    long my_in_circle = my_in_counter(itrs_per_thread);

    pthread_mutex_lock(&mutex);
    in_circle += my_in_circle;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main(int argc, char* argv[]) {

    // Reset global variable no_of_threads.
    no_of_threads = 0;
    // Extract no of thread from the command-line arguments.
    if(argc > 1) {
        no_of_threads = atoi(argv[1]);
    }
    if (no_of_threads <= 0) {
        printf("Error: argument 1, No of threads should be a positive integer!");
        exit(-1);
    }

    // Reset shared variable.
    in_circle = 0;
    pthread_t threads[no_of_threads];
    struct timespec requestStart, requestEnd;

    // Record the starting time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestStart);

    // Wait till all the threads finishes.
    for(int i=0; i<no_of_threads; i++) {
        pthread_create(&threads[i], NULL, runner, (void*)i);
    }

    // Collect all results and finalize.
    for(int i=0; i<no_of_threads; i++) {
        pthread_join(threads[i],NULL);
    }

    // Estimate Pi.
    pi = estimate_pi(in_circle, NO_OF_ITERATIONS);

    // Record finishing time of Pi estimation.
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    // Calculates the elapsed time.
    double elapsed_time = get_elapsed_time(requestStart, requestEnd);

    printf("No of trials: %d , No of threads: %d, estimate of Pi: %g, elapsed time: %1f\n", NO_OF_ITERATIONS, no_of_threads, pi, elapsed_time);

    // Destroy global mutex resource.
    pthread_mutex_destroy(&mutex);
    // Before exit wait until all spawned threads are done.
    pthread_exit(NULL);
}
