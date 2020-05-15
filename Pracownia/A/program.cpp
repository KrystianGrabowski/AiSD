#include <stdio.h>
#include <vector>

#define MAX_L 10001

struct tile {
    int l;
    int m;
    int r;
};

int main() {
    int n, k, j;
    std::vector<tile> tiles [MAX_L];
    std::vector<tile> result;
    tile tile0;
    bool startExists = false;
    bool endExists = false;

    // Read data
    if (!scanf("%d", &n)) { return 0; }
    
    for (int i=0; i<n; i++) {
        if (!scanf("%d %d %d", &tile0.l, &tile0.m, &tile0.r)) { return 0; }
        tiles[tile0.l].push_back(tile0);
        if (tile0.l == 0) { startExists = true; }
        if (tile0.r == 0) { endExists = true; }
    }

    // If end/start tile doesn't exist, solution cannot be found
    if (!startExists || !endExists) { printf("BRAK"); return 0; }

    // Find a way out
    k = 0;
   while(true) {
        tile0 = tiles[k].back();
        result.push_back(tile0);
        tiles[k].pop_back();

        if (tile0.r == 0) { break; }
        k = tile0.r;
        if (tiles[tile0.r].empty()) {
            result.pop_back();
            j = tile0.l;
            while (tiles[j].empty()) {
                if (j == 0) { printf("BRAK"); return 0; }
                tile0 = result.back();
                result.pop_back();
                j = tile0.l;
            }
            k = j;
        }
    }
    
    // Print result
    printf("%lu\n", result.size());
    for (long unsigned i=0; i<result.size(); i++) {
        printf("%d %d %d\n", result[i].l, result[i].m, result[i].r );
    }
    return 0;

}