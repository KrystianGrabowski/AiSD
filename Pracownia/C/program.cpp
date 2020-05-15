#include <stdio.h>
#include <vector>

struct coin {
    int p;
    int w;
};

struct nav_struct {
    __int64_t v = 0;
    int prev;
};

int main() {
    int f, c;
    coin c0;
    std::vector<coin> coins;

    // Read data
    if (!scanf("%d", &f)) { return 0; }
    if (!scanf("%d", &c)) { return 0; }
    for (int i=0; i<c; i++) {
        if (!scanf("%d %d", &c0.p, &c0.w)) { return 0; }
        coins.push_back(c0);
    }

    // Values are stored in min and max arrays. If value equals 0 then solution doesn't exists;
    std::vector<nav_struct> min_value(f+1);
    std::vector<nav_struct> max_value(f+1);
    int iter, cmpl_weight;

    for (int i=1; i<f+1; i++) {
        iter = 0;
        // Iterate through coins and update if coin is smaller or equal than current max weight
        while (iter < c) {
            cmpl_weight = i-coins[iter].w;
            if (coins[iter].w <= i && (min_value[cmpl_weight].v != 0 || cmpl_weight == 0)) {
                if ((min_value[i].v == 0) || (min_value[i].v > coins[iter].p + min_value[cmpl_weight].v)) {
                    min_value[i].v = coins[iter].p + min_value[cmpl_weight].v;
                    min_value[i].prev = iter;
                }
                if ((max_value[i].v == 0) || (max_value[i].v < coins[iter].p + max_value[cmpl_weight].v)) {
                    max_value[i].v = coins[iter].p + max_value[cmpl_weight].v;
                    max_value[i].prev = iter;
                }
            }
            iter++;
        }
    }

    // Print answer
    if (max_value[f].v != 0) {
        std::vector<int> coins_amount(c, 0);

        // Create answer
        printf("TAK\n");
        iter = f;

        // Min value
        while (iter != 0) {
            coins_amount[min_value[iter].prev] += 1;
            iter = iter - coins[min_value[iter].prev].w;
        }
        printf("%ld\n", min_value[f].v);
        for (int i=0; i<c; i++) {
            printf("%d ", coins_amount[i]);
            coins_amount[i] = 0;
        }

        // Max value
        iter = f;
        while (iter != 0) {
            coins_amount[max_value[iter].prev] += 1;
            iter = iter - coins[max_value[iter].prev].w;
        }
        printf("\n");
        printf("%ld\n", max_value[f].v);
        for (int i=0; i<c; i++) {
            printf("%d ", coins_amount[i]);
        }
    }
    else {
        printf("NIE\n");
    }


    return 0;

}
