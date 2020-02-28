#include <stdio.h>

int main() {
    int a, b;
    if (!scanf("%d %d", &a, &b)) { return 0; }
    if (a > b) {
        int temp = b;
        b = a;
        a = temp;
    }
    for (int i=a; i<=b; i++) {
        printf("%d\n", i);
    }
    
    return 0;
}