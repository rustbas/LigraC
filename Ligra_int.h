#ifndef ASSERT_H
#define ASSERT_H
#include <assert.h>
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef OMP_H
#define OMP_H
#include <omp.h>
#endif

#ifndef UNIMPLEMENTED
#define UNIMPLEMENTED \
do { \
	fprintf(stderr, "%s:%d: UNIMPLEMENTED\n", __FILE__, __LINE__); \
	exit(1); \
} while(0);
#endif

typedef struct {
    unsigned int n;
    unsigned int m;
    int** MM;
} M_i;

M_i zeroM_i(unsigned int n, unsigned int m) {
    M_i res;
    res.n = n;
    res.m = m;

    res.MM = (int**) malloc(n * sizeof(int*));
    for (int i=0; i<n; i++) {
        res.MM[i] = (int*) malloc(m * sizeof(int));
    }

    return res;
}

M_i eyeM_i(unsigned int n) {
    M_i res = zeroM_i(n, n);
    for (int i=0; i<n; i++) {
        res.MM[i][i] = 1;
    }

    return res;
}

M_i randM_i(unsigned int n, unsigned int m, int a, int b) {
    M_i MM = zeroM_i(n, m);

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            MM.MM[i][j] = (rand() % (a - b - 1)) + a;
        }
    }

    return MM;
}

M_i addM_i(M_i A, M_i B) {
    if ((A.n != B.n) || (A.m != B.m)) {
        printf("Dimensions must be equal!\n");
        printf("A = %dx%d, B = %dx%d\n", A.n, A.m, B.n, B.m);
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            A.MM[i][j] += B.MM[i][j];
        }
    }

    return A;
}

M_i subM_i(M_i A, M_i B) {
    if ((A.n != B.n) || (A.m != B.m)) {
        printf("Dimensions must be equal!\n");
        printf("A = %dx%d, B = %dx%d\n", A.n, A.m, B.n, B.m);
        exit(EXIT_FAILURE);
    }

    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            A.MM[i][j] -= A.MM[i][j];
        }
    }

    return A;
}

M_i mulM_i(M_i A, M_i B) {
    if (A.m != B.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d, B = %dx%d\n", A.n, A.m, B.n, B.m);
        exit(EXIT_FAILURE);
    }

    M_i C = zeroM_i(A.n, B.m);

    for (int i=0; i<A.n; ++i) {
        for (int j=0; j<B.m; ++j) {
            for (int k=0; k<A.m; ++k) {
                C.MM[i][j] += A.MM[i][k] * B.MM[k][j];
            }
        }
    }

    return C;
}

static M_i minorM_i(M_i A, unsigned int k, unsigned int l) {
    M_i temp = zeroM_i(A.n-1, A.m-1);

    for (int i=0; i<A.n; ++i) {
        for (int j=0; j<A.n; ++j) {
            if ((i<k)&&(j<l)) {
                temp.MM[i][j] = A.MM[i][j];
            } else if ((i<k)&&(j>l)) {
                temp.MM[i][j-1] = A.MM[i][j];
            } else if ((i>k)&&(j<l)) {
                temp.MM[i-1][j] = A.MM[i][j];
            } else if ((i>k)&&(j>l)) {
                temp.MM[i-1][j-1] = A.MM[i][j];
            } else {
                continue;
            }

        }
    }

    return temp;
}

int detM_i(M_i A) {
    if (A.m != A.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d\n", A.n, A.m);
        exit(EXIT_FAILURE);
    }

    if (A.n == 2) {
        return A.MM[0][0]*A.MM[1][1] - A.MM[0][1]*A.MM[1][0];
    } else {
        int res = 0;
        for (int i=0; i<A.n; i++) {
            res += pow(-1, i)*A.MM[0][i]*detM_i(minorM_i(A, 0, i));
        }
        return res;
    }
}

M_i transposeM_i(M_i A) {
    M_i res = zeroM_i(A.m, A.n);


    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            res.MM[j][i] = A.MM[i][j];
        }
    }

    return res;
}

M_i mulConstM_i(M_i A, int C) {
    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            A.MM[i][j] *= C;
        }
    }

    return A;
}

M_i add_constM_i(M_i MM, int C) {
    for (int i=0; i<MM.n; i++) {
        for (int j=0; j<MM.m; j++) {
            MM.MM[i][j] += C;
        }
    }

    return MM;
}

void printM_i(M_i MM) {
    unsigned int n = MM.n;
    unsigned int m = MM.m;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%d ", MM.MM[i][j]);
        }
        printf("\n");
    }
}

void freeM_i(M_i A) {
    for (int i=0; i<A.n; ++i) {
        free(A.MM[i]);
    }
    free(A.MM);
}
