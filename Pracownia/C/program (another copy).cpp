#include <stdio.h>
#include <vector>
#include <algorithm>

struct coin {
    int p;
    int w;
    int8_t originial_position ;
};

struct nav_struct {
    int64_t v = 0;
    int prev;
};

bool compare_coins_by_weight(const coin &c0, const coin &c1) {
    return c0.w < c1.w || (c0.w == c1.w && c0.p < c1.p);
}

int main() {
    int f, c;
    coin c0;
    std::vector<coin> coins;

    // Read data
    if (!scanf("%d", &f)) { return 0; }
    if (!scanf("%d", &c)) { return 0; }
    for (int i=0; i<c; i++) {
        if (!scanf("%d %d", &c0.p, &c0.w)) { return 0; }
        c0.originial_position = (int8_t)i;
        coins.push_back(c0);
    }

    std::sort(coins.begin(), coins.end(), compare_coins_by_weight);

    // Values are stored in min and max arrays. If value equals 0 then solution doesn't exists;
    std::vector<nav_struct> min_value(f+1);
    std::vector<nav_struct> max_value(f+1);
    int iter, weight_wo_elem;

    for (int i=1; i<f+1; i++) {
        iter = 0;
        // Iterate through coins and update if coin is smaller or equal than current max weight
        while (coins[iter].w <= i && iter < c) {
            weight_wo_elem = i-coins[iter].w;
            if (iter == 0 || (iter > 0 && coins[iter-1].w != coins[iter].w)) {
                if ((min_value[i].v == 0) || (min_value[i].v > coins[iter].p + min_value[weight_wo_elem].v)) {
                    if (min_value[weight_wo_elem].v != 0 || weight_wo_elem == 0) {
                        min_value[i].v = coins[iter].p + min_value[weight_wo_elem].v;
                        min_value[i].prev = iter;
                    }
                }
            }
            if (iter + 1 >= c || coins[iter+1].w != coins[iter].w) {
                if ((max_value[i].v == 0) || (max_value[i].v < coins[iter].p + max_value[weight_wo_elem].v)) {
                    if (max_value[weight_wo_elem].v != 0 || weight_wo_elem == 0) {
                        max_value[i].v = coins[iter].p + max_value[weight_wo_elem].v;
                        max_value[i].prev = iter;
                    }
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
            coins_amount[coins[min_value[iter].prev].originial_position] += 1;
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
            coins_amount[coins[max_value[iter].prev].originial_position] += 1;
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