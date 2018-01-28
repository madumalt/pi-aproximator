## Compile and run sequential implementation of motecalo algorithm in unix.
gcc serial-impl.c -o serial-impl -lm
./serial-impl

## Compile and run parallel implementation of motecalo algorithm in unix.
gcc pthread-impl.c -o pthread-impl -lm -lpthread
./pthread-impl 4

## Compile and run sequential implementation of numerical algorithm in unix.
gcc numerical-serial-impl.c -o numerical-serial-impl
./numerical-serial-impl
reference: http://webcem01.cem.itesm.mx:8005/apps/s201213/tc3035/notes_computing_pi/

## Notes:
While Implementing the parallel version of PI calculation, the elapsed time was higher compared to serial version.
The reason was random() and rand() have some locking mechanism which does not give the benifit of parallel execution.
Using rand_r of stdlib.h did solve the problem.

