#include<stdio.h>

int main(){
    int t, iter;
    scanf("%d", &t);
    int binary[32];
    long long int val, res;
    int a, b, m;
    for (int i=0; i<t; i++){
        scanf("%d %d %d",&a, &b, &m);
        iter = 0;
        // Binary representation of an exponent
        while (b > 0){
            binary[iter++] = b % 2;
            b >>= 1;
        }
        val = a % m;
        res = 1;
        // 117 = 1110101
        // 5^117 = 5^1 * 5^4 * 5^16 * 5^32 * 5^64 
        for (int i=0; i<iter; i++) {
            if (binary[i] == 1){
                res = (res * val) % m;
            }
            val = (val * val) % m;
        }
        printf("%lld\n", res);
    }
    return 0;
}