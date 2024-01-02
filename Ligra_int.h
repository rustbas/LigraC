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
