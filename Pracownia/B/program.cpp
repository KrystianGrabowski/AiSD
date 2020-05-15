#include <stdio.h>
#include <vector>
#include <cmath>
#include <algorithm>
#define THRESHOLD 6

struct point {
    int x;
    int y;
};

struct triangle {
    point x1;
    point x2;
    point x3;
    double perimeter;
};

std::vector<point> points_x;

bool compare_points_by_x(const point &p0, const point &p1) {
    return p0.x < p1.x;
}

bool compare_points_by_y(const point &p0, const point &p1) {
    return p0.y < p1.y;
}

triangle brute_solution(int start, int end) {
    double smallest_perimeter = -1;
    double perimeter;
    double d1, d2, d3;
    triangle triangle0;
    
    for (int k=start; k<=end; k++) {
        for (int l=k+1; l<=end; l++) {
            for (int g=l+1; g<=end; g++) {
                d1 = sqrt( pow(points_x[l].x - points_x[k].x, 2 ) + pow(points_x[l].y - points_x[k].y, 2 ));
                d2 = sqrt( pow(points_x[l].x - points_x[g].x, 2 ) + pow(points_x[l].y - points_x[g].y, 2 ));
                d3 = sqrt( pow(points_x[g].x - points_x[k].x, 2 ) + pow(points_x[g].y - points_x[k].y, 2 ));
                perimeter = d1 + d2 + d3;
                if (smallest_perimeter > perimeter || smallest_perimeter == -1) {
                    triangle0.x1 = points_x[k];
                    triangle0.x2 = points_x[l];
                    triangle0.x3 = points_x[g];
                    triangle0.perimeter = perimeter;
                    smallest_perimeter = perimeter;
                }
            }
        }
    }
    return triangle0;
}

triangle smallerst_triangle(int start, int end) {
    std::vector<point> points;
    int size = end - start + 1;
    if  (size < THRESHOLD && size > 2) {
        return brute_solution(start, end);
    }
    int middle = (end + start) / 2;
    int middle_val = points_x[middle].x;
    triangle left_max = smallerst_triangle(start, middle);
    triangle right_max = smallerst_triangle(middle+1, end);
    triangle min_triangle = left_max.perimeter < right_max.perimeter ? left_max : right_max;
    int points_size = (int)points_x.size();

    for (int i=middle+1; i<=end; i++) {
        if (abs(points_x[i].x - middle_val) < min_triangle.perimeter/2) {
            points.push_back(points_x[i]);
            continue;
        }
        break;
    }
    for (int i=middle; i>=start; i--) {
        if (abs(points_x[i].x - middle_val) < min_triangle.perimeter/2) {
            points.push_back(points_x[i]);
            continue;
        }
        break;
    }
    std::sort(points.begin(), points.end(), compare_points_by_y);

    double perimeter;
    double d1, d2, d3;
    points_size = (int)points.size();
    for (int k=0; k<=points_size-2; k++) {
        int limit = std::min(k+7, points_size-1);
        for (int l=k+1; l<=limit; l++) {
            for (int g=l+1; g<=limit; g++) {
                d1 = sqrt( pow(points[l].x - points[k].x, 2 ) + pow(points[l].y - points[k].y, 2 ));
                d2 = sqrt( pow(points[l].x - points[g].x, 2 ) + pow(points[l].y - points[g].y, 2 ));
                d3 = sqrt( pow(points[g].x - points[k].x, 2 ) + pow(points[g].y - points[k].y, 2 ));
                perimeter = d1 + d2 + d3;
                if (min_triangle.perimeter > perimeter) {
                    min_triangle.x1 = points[k];
                    min_triangle.x2 = points[l];
                    min_triangle.x3 = points[g];
                    min_triangle.perimeter = perimeter;
                }
            }
        }
    }
    return min_triangle; 
}

int main() {
    int n;
    point point0;

    // Read data
    if (!scanf("%d", &n)) { return 0; }
    for (int i=0; i<n; i++) {
        if (!scanf("%d %d", &point0.x, &point0.y)) { return 0; }
        points_x.push_back(point0);
    }

    // Sort by x
    std::sort(points_x.begin(), points_x.end(), compare_points_by_x);

    triangle t0 = smallerst_triangle(0, n-1);

    printf("%d %d\n%d %d\n%d %d\n", t0.x1.x, t0.x1.y, t0.x2.x, t0.x2.y , t0.x3.x, t0.x3.y);
    return 0;

}