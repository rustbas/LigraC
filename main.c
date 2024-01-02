#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

#include "Ligra_int.h"

int main(int argc, char** argv) {
    MM_i test = zeroMM_i(5, 5);

    printMM_i(test);

    add_constMM_i(test, -3);

    printMM_i(test);

    return 0;
}
