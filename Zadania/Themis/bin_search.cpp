#include<stdio.h>
#include<stdint.h>
#include<math.h>

int main(){
    int32_t n,m;
    scanf("%d", &n);
    int array[n];
    for (int i=0; i<n; i++){
        scanf("%d", &array[i]);
    }
    int l, r, c, q;
    scanf("%d", &m);
    for (int i=0; i<m; i++) {
        scanf("%d", &q);
        l = 0;
        r = n;
        while(l < r) {
            c = (l + r) >> 1;
            if (q > array[c]) {
                l = ++c;
            }
            else {
                r = c;
            }
        }
        printf("%d ", n-c);
    }
    return 0;
}

