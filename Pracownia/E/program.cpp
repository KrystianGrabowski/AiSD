#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>

struct point {
    int a;
    int b;
    int c;
    int prev;
    long value;
};

bool compare_points_by_x_y(const point &p0, const point &p1) {
    return p0.b < p1.b || (p0.b == p1.b && p0.a < p1.a);
}

bool compare_points_by_y_x(const point &p0, const point &p1) {
    return p0.a < p1.a || (p0.a == p1.a && p0.b < p1.b);
}

int main() {
    int n, m, k;
    std::vector<point> points;
    std::vector<point> res_points;

    // Read data
    if (!scanf("%d %d", &n, &m)) { return 0; }
    if (!scanf("%d", &k)) { return 0; }
    for (int i=0; i<k; i++) {
        point point0;
        if (!scanf("%d %d %d", &point0.a, &point0.b, &point0.c)) { return 0; }
        point0.prev = -1;
        point0.value = point0.c;
        points.push_back(point0);
    }

    std::sort(points.begin(), points.end(), compare_points_by_x_y);
    std::vector<point> points_y(points);
    std::sort(points.begin(), points.end(), compare_points_by_y_x);
   
   for (int i=0; i<k; i++) {
       printf("%d %d %d | %d %d %d\n", points[i].a, points[i].b, points[i].c, points_y[i].a, points_y[i].b, points_y[i].c);
   }

    // for (int i=0; i<k; i++) {
    //     for (int j=0; j<k; j++) {
    //         if (i == j) {continue;}
    //         if (points[j].a >= points[i].a && points[j].b >= points[i].b) {
    //             if (points[i].value + points[j].c > points[j].value) {
    //                 points[j].value = points[i].value + points[j].c;
    //                 points[j].prev = i;
    //             }
    //         }
    //     }
    // }

    // long max = 0;
    // int max_id = 0;
    // for (int i=0; i<k; i++) {
    //     if (points[i].value > max) {
    //         max_id = i;
    //         max = points[i].value;
    //     }
    // }

    // int iter = max_id;
    // while(iter != -1) {
    //     res_points.push_back(points[iter]);
    //     iter = points[iter].prev;
    // }

    // point point1;
    // printf("%ld\n", max);
    // printf("%d\n", (int)res_points.size());
    // while(res_points.size() != 0) {
    //     point1 = res_points.back();
    //     res_points.pop_back();
    //     printf("%d %d\n", point1.a, point1.b);
    // }


    return 0;

}