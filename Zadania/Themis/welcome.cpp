/*
Krystian Grabowski
288282
AKUN
*/

#include <stdio.h>
#define NUM 2020

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    if (a <= 0) {a = 1;}
    for (int i=a; i<=b; i++) {
        if (NUM % i == 0) {
            printf("%d\n", i);
        }
    }
    return 0;
}