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
    if(array.size() < 15) {
        std::sort(array.begin(), array.end());
        return array[k-1];
    }
    std::vector<int> smaller, greater, medians, ad_hoc_med;

    int iter = 0;
    int iter_end, pivot;
    int size = (int)array.size();

    // choose pivot START
    // iterate from 0 to floor(size/5) - 1 and extract medians from sets with five elements
    for (int i=0; i<std::floor(size/5); i++) {
        iter = 5 * i;
        iter_end = iter + 5;
        while (iter < iter_end) {
            ad_hoc_med.push_back(array[iter]);
            iter++;
        }
        std::sort(ad_hoc_med.begin(), ad_hoc_med.end());
        medians.push_back(ad_hoc_med[2]);
        ad_hoc_med.clear();
    }

    // extract last median from set with number of elements less than five.
    while (iter < size) {
        ad_hoc_med.push_back(array[iter++]);
    }
    if (ad_hoc_med.size() > 0) {
        std::sort(ad_hoc_med.begin(), ad_hoc_med.end());
        medians.push_back(ad_hoc_med[middle_element_id((int)ad_hoc_med.size())]);
    } 

    // Get median of medians
    pivot = selection(medians, medians.size() / 2 + 1);
    // choose pivot END


    // Split into grater smaller equal
    for (int i=0; i<size; i++) {
        if (array[i] < pivot) {
            smaller.push_back(array[i]);
        }
        else if (array[i] > pivot) {
            greater.push_back(array[i]);
        }
    }

    // Where should i look for an element?
    int smaller_size = (int)smaller.size();
    int greater_size = (int)greater.size();
    if (k <= smaller_size) {
        return selection(smaller, k);
    }
    else if (k > size - greater_size) {
        return selection(greater, k - (size - greater_size));
    }
    else {
        return pivot; 
    }

    return selection(medians, medians.size() / 2 + 1);
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