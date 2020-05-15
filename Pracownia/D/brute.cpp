#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>

int middle_element_id(int size) {
    if (size == 1) {
        return 0;
    }
    else {
        return size/2;
    }
}

int selection(std::vector<int> array, int k) {
    std::sort(array.begin(), array.end());
    return array[k-1];
}

int main() {
    int n, k;
    std::vector<int> array;
    int c;

    // Read data
    if (!scanf("%d %d", &n, &k)) { return 0; }
    for (int i=0; i<n; i++) {
        if (!scanf("%d", &c)) { return 0; }
        array.push_back(c);
    }

    printf("%d\n", selection(array, k));

    return 0;

}