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
    float** MM;
} M_f;

M_f zeroM_f(unsigned int n, unsigned int m) {
    M_f res;
    res.n = n;
    res.m = m;

    res.MM = (float**) malloc(n * sizeof(float*));
    for (int i=0; i<n; i++) {
        res.MM[i] = (float*) malloc(m * sizeof(float));
    }

    return res;
}

M_f eyeM_f(unsigned int n) {
    M_f res = zeroM_f(n, n);
    for (int i=0; i<n; i++) {
        res.MM[i][i] = 1;
    }

    return res;
}

M_f randM_f(unsigned int n, unsigned int m, float a, float b) {
    M_f MM = zeroM_f(n, m);

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            MM.MM[i][j] = (((float) rand()) / RAND_MAX) * (b - a) + a;
        }
    }

    return MM;
}

M_f addM_f(M_f A, M_f B) {
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

M_f subM_f(M_f A, M_f B) {
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

M_f mulM_f(M_f A, M_f B) {
    if (A.m != B.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d, B = %dx%d\n", A.n, A.m, B.n, B.m);
        exit(EXIT_FAILURE);
    }

    M_f C = zeroM_f(A.n, B.m);

    for (int i=0; i<A.n; ++i) {
        for (int j=0; j<B.m; ++j) {
            for (int k=0; k<A.m; ++k) {
                C.MM[i][j] += A.MM[i][k] * B.MM[k][j];
            }
        }
    }

    return C;
}

static M_f minorM_f(M_f A, unsigned int k, unsigned int l) {
    M_f temp = zeroM_f(A.n-1, A.m-1);

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

float detM_f(M_f A) {
    if (A.m != A.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d\n", A.n, A.m);
        exit(EXIT_FAILURE);
    }

    if (A.n == 1) {
        return A.MM[0][0];
    } else if (A.n == 2) {
        return A.MM[0][0]*A.MM[1][1] - A.MM[0][1]*A.MM[1][0];
    } else {
        float res = 0;
        for (int i=0; i<A.n; i++) {
            res += pow(-1, i)*A.MM[0][i]*detM_f(minorM_f(A, 0, i));
        }
        return res;
    }
}

float traceM_f(M_f A) {
    if (A.m != A.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d\n", A.n, A.m);
        exit(EXIT_FAILURE);
    }

    float res = 1.0;
    for (int i=0; i<A.n; i++) {
        res *= A.MM[i][i];
    }

    return res;
}

float det_fastM_f(M_f A) {
    if (A.m != A.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d\n", A.n, A.m);
        exit(EXIT_FAILURE);
    }

    int i, j, k;

    UNIMPLEMENTED

    return traceM_f(A);
}

M_f transposeM_f(M_f A) {
    M_f res = zeroM_f(A.m, A.n);


    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            res.MM[j][i] = A.MM[i][j];
        }
    }

    return res;
}

M_f invM_f(M_f A) {
    if (A.m != A.n) {
        printf("Dimensions must be consistent!\n");
        printf("A = %dx%d\n", A.n, A.m);
        exit(EXIT_FAILURE);
    }

    float det = detM_f(A);
    float temp;

    M_f result = zeroM_f(A.n, A.m);

    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            temp = detM_f(minorM_f(transposeM_f(A), i, j));
            result.MM[i][j] = powf(-1.0f, i+j) * temp / det;
        }
    }

    return result;
}

M_f mulConstM_f(M_f A, float C) {
    for (int i=0; i<A.n; i++) {
        for (int j=0; j<A.m; j++) {
            A.MM[i][j] *= C;
        }
    }

    return A;
}

M_f add_constM_f(M_f MM, float C) {
    for (int i=0; i<MM.n; i++) {
        for (int j=0; j<MM.m; j++) {
            MM.MM[i][j] += C;
        }
    }

    return MM;
}

void printM_f(M_f MM) {
    unsigned int n = MM.n;
    unsigned int m = MM.m;

    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            printf("%f ", MM.MM[i][j]);
        }
        printf("\n");
    }
}

void freeM_f(M_f A) {
    for (int i=0; i<A.n; ++i) {
        free(A.MM[i]);
    }
    free(A.MM);
}
