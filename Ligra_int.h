#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif

typedef struct {
    unsigned int n;
    unsigned int m;
    int** MM;
} MM_i;

MM_i zeroMM_i(unsigned int n, unsigned int m) {

    MM_i res;
    res.n = n;
    res.m = m;

    res.MM = (int**) malloc(n * sizeof(int*));
    for (int i=0; i<n; i++) {
        res.MM[i] = (int*) malloc(m * sizeof(int));
    }

    return res;
}

MM_i randMM_i(unsigned int n, unsigned int m, int a, int b) {
    MM_i MM = zeroMM_i(n, m);

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            MM.MM[i][j] = (rand() % (a - b - 1)) + a;
        }
    }

    return MM;
}

MM_i addMM_i(MM_i a, MM_i b) {
    for (int i=0; i<a.n; i++) {
        for (int j=0; j<a.m; j++) {
            a.MM[i][j] += b.MM[i][j];
        }
    }

    return a;
}

MM_i subMM_i(MM_i a, MM_i b) {
    for (int i=0; i<a.n; i++) {
        for (int j=0; j<a.m; j++) {
            a.MM[i][j] -= b.MM[i][j];
        }
    }

    return a;
}

MM_i mulMM_i(MM_i A, MM_i B) {
    MM_i C = zeroMM_i(A.n, B.m);

    for (int i=0; i<A.n; ++i) {
        for (int j=0; j<B.m; ++j) {
            for (int k=0; k<A.m; ++k) {
                C.MM[i][j] += A.MM[i][k] * B.MM[k][j];
            }
        }
    }

    return C;
}

MM_i add_constMM_i(MM_i MM, int C) {
    for (int i=0; i<MM.n; i++) {
        for (int j=0; j<MM.m; j++) {
            MM.MM[i][j] += C;
        }
    }

    return MM;
}

void printMM_i(MM_i MM) {
    unsigned int n = MM.n;
    unsigned int m = MM.m;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%d ", MM.MM[i][j]);
        }
        printf("\n");
    }
}
