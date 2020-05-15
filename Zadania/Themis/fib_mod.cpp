#include<stdio.h>

struct matrix {
    long long int matrix[2][2];
};

matrix matrix_mult(matrix m0, matrix m1, int m) {
    matrix m2 = {{{
        (m0.matrix[0][0] * m1.matrix[0][0] + m0.matrix[0][1] * m1.matrix[1][0]) % m,
        (m0.matrix[1][0] * m1.matrix[0][0] + m0.matrix[1][1] * m1.matrix[1][0]) % m,
    },{
        (m0.matrix[0][0] * m1.matrix[1][0] + m0.matrix[0][1] * m1.matrix[1][1]) % m,
        (m0.matrix[1][0] * m1.matrix[0][1] + m0.matrix[1][1] * m1.matrix[1][1]) % m,
    }}};
    return m2;
}

matrix matrix_pow(matrix mx, int n, int m) {
    if (n == 0) {
        matrix id = {{{1, 0},{0, 1}}};
        return id;
    }
    matrix m0 = matrix_pow(mx, n>>1, m);
    m0 = matrix_mult(m0, m0, m);
    if (n % 2 == 1) {
        m0 = matrix_mult(mx, m0, m);
    }
    return m0;
}

int matrix_fib(int n, int m) {
    matrix initial_matrix = {{{0, 1}, {1, 1}}};
    matrix result = matrix_pow(initial_matrix, n-1, m);
    return result.matrix[1][1];
}

int main() {
    int t, n, m;
    scanf("%d", &t);
    for (int i=0; i<t; i++) {
        scanf("%d %d", &n, &m);
        printf("%d\n", matrix_fib(n, m));
    }
}