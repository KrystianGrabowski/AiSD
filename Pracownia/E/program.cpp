#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>

struct point {
    int a;
    int b;
    int c;
    int prev;
    long value;
};

bool compare_points_by_y_x(const point &p0, const point &p1) {
    return p0.b < p1.b || (p0.b == p1.b && p0.a < p1.a);
}

bool compare_points_by_x_y(const point &p0, const point &p1) {
    return p0.b < p1.b || (p0.b == p1.b && p0.a < p1.a);
}

int main() {
    int n, m, k;
    std::vector<point> points;
    std::vector<point> level_points;
    std::vector<point> visited_points;

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

    std::sort(points.begin(), points.end(), compare_points_by_y_x);
    point point_start;
    point_start.a = 0;
    point_start.b = 0;
    point_start.c = 0;
    point_start.prev = -1;
    point_start.value = 0; 
    visited_points.push_back(point_start);

    int current_y;
    int iter = 0;
    
    while (iter < k) {
        current_y = points[iter].b;
        while (current_y == points[iter].b && iter < k) {
            level_points.push_back(points[iter++]);
        }
        

        for (int i=0; i<(int)level_points.size(); i++) {
            int pointer = (int)visited_points.size() - 1;
            //Binsearch ToDo
            while (pointer > -1 && visited_points[pointer].a > level_points[i].a) {
                pointer--;
            }
            if (i != 0) {
                if (visited_points[pointer].value > level_points[i-1].value) {
                    level_points[i].value = visited_points[pointer].value + level_points[i].c;
                }
                else {
                    level_points[i].value = level_points[i-1].value + level_points[i].c;
                }
            }
            else {
                level_points[i].value = visited_points[pointer].value + level_points[i].c;
            }  
        }

        visited_points.insert( visited_points.end(), level_points.begin(), level_points.end() );
        std::sort(visited_points.begin(), visited_points.end(), compare_points_by_x_y);
        printf("_-----------------_\n");
        for (int i=0; i<(int)visited_points.size(); i++) {
            printf("%d %d %ld %d\n", visited_points[i].a, visited_points[i].b, visited_points[i].value, visited_points[i].prev);
        }
        level_points.clear();
        int fd;
        scanf("%d", &fd);
    }



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