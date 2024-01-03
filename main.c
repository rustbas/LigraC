#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#include "Ligra_int.h"

int main(int argc, char** argv) {
    srand(time(0));

    MM_i test1 = randMM_i(1, 3, -3, 3);
    MM_i test2 = randMM_i(2, 2, 0, 10);
    MM_i test3 = eyeMM_i(5);

    printMM_i(test1);
    printf("\n");
    /*printMM_i(test3);*/
    printf("\n");
    /*printMM_i(mulMM_i(test1, test3));*/

    printMM_i(mulConstMM_i(test1, 5));

    freeMM_i(test1);
    freeMM_i(test2);
    freeMM_i(test3);

    return 0;
}
