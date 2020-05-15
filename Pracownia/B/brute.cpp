#include <stdio.h>
#include <vector>
#include <cmath>
#include <limits.h>

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


int main() {
    int n;
    std::vector<point> points;
    point point0;

    if (!scanf("%d", &n)) { return 0; }
    
    for (int i=0; i<n; i++) {
        if (!scanf("%d %d", &point0.x, &point0.y)) { return 0; }
        points.push_back(point0);
    }

    double smallest_perimeter = INT_MAX;
    double perimeter;
    triangle t0;
    double d1, d2, d3;
    for (int k=0; k<n; k++) {
        for (int l=k+1; l<n; l++) {
            for (int g=l+1; g<n; g++) {
                d1 = sqrt( pow(points[l].x - points[k].x, 2 ) + pow(points[l].y - points[k].y, 2 ));
                d2 = sqrt( pow(points[l].x - points[g].x, 2 ) + pow(points[l].y - points[g].y, 2 ));
                d3 = sqrt( pow(points[g].x - points[k].x, 2 ) + pow(points[g].y - points[k].y, 2 ));
                perimeter = d1 + d2 + d3;
                if (smallest_perimeter > perimeter) {
                    t0.x1 = points[l];
                    t0.x2 = points[k];
                    t0.x3 = points[g];
                    t0.perimeter = perimeter;
                    smallest_perimeter = perimeter;

                }
            }
        }
    }
    printf("%d %d\n", t0.x1.x, t0.x1.y);
    printf("%d %d\n", t0.x2.x, t0.x2.y);
    printf("%d %d\n", t0.x3.x, t0.x3.y);
    // printf("%f", t0.perimeter);
    return 0;

}