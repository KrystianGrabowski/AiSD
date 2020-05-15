#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

struct point {
    int id;
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
    return p0.a < p1.a || (p0.a == p1.a && p0.b < p1.b);
}

int main() {
    int n, m, k;
    std::map<int, point> demo;

    point point4;
    point4.a = 1;
    point4.b = 1;
    point4.c = 0;
    point4.id = -1;
    point4.prev = -1;
    point4.value = 0;

    demo.insert(std::pair<int, point>(1, point4 ));
    auto iet = demo.lower_bound(3);  
    if (iet != demo.begin()) iet--;
    printf("ITER %d\n", iet->second.id);
    std::vector<point> res_points;
    std::vector<point> points;
    std::vector<point> level_points;
    std::vector<point> visited_points;

    // Read data
    int it = 0;
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
    for (int i=0; i<k; i++) {
        points[i].id = it++;
    }
    if (points[0].a != 1 || points[0].b != 1) {
        point point_start;
        point_start.a = 1;
        point_start.b = 1;
        point_start.c = 0;
        point_start.id = -1;
        point_start.prev = -1;
        point_start.value = 0;
        visited_points.push_back(point_start);
    }


    int current_y = 1;
    int iter_y = 0;
    
    while (iter_y < k && points[iter_y].b == current_y) {
        visited_points.push_back(points[iter_y++]);
    }

    for (int i=0; i<(int)visited_points.size()-1; i++) {
        visited_points[i+1].value = visited_points[i].value + visited_points[i+1].c;
    }

    while (iter_y < k) {
        current_y = points[iter_y].b;
        while (current_y == points[iter_y].b && iter_y < k) {
            level_points.push_back(points[iter_y++]);
        }
        

        for (int i=0; i<(int)level_points.size(); i++) {
            int pointer = (int)visited_points.size() - 1;
            //Binsearch ToDo
            while (pointer > 0 && visited_points[pointer].a > level_points[i].a) {
                pointer--;
            }
            if (i != 0) {
                if (visited_points[pointer].value > level_points[i-1].value) {
                    level_points[i].value = visited_points[pointer].value + level_points[i].c;
                    points[level_points[i].id].prev = visited_points[pointer].id;
                    level_points[i].prev = visited_points[pointer].id;
                }
                else {
                    level_points[i].value = level_points[i-1].value + level_points[i].c;
                    points[level_points[i].id].prev = level_points[i-1].id;
                    level_points[i].prev = level_points[i-1].id;
                }
            }
            else {
                level_points[i].value = visited_points[pointer].value + level_points[i].c;
                points[level_points[i].id].prev = visited_points[pointer].id;
                level_points[i].prev = visited_points[pointer].id;

            }  
        }

        visited_points.insert( visited_points.end(), level_points.begin(), level_points.end() );
        std::sort(visited_points.begin(), visited_points.end(), compare_points_by_x_y);
        level_points.clear();
        int mx = visited_points[0].value;
        //printf("SIZE %d\n", (int)visited_points.size());
        int ikkk = 0;
        while(ikkk < (int)visited_points.size()) {
            //printf("REMOVE ITER %d %d val:%d (mx:%d)\n", visited_points[ikkk].a, visited_points[ikkk].b, visited_points[ikkk].value, mx);
            if (mx > visited_points[ikkk].value) {
                visited_points.erase(visited_points.begin()+ikkk);
            }
            else {
                mx = visited_points[ikkk].value;
                ikkk++;
            }
        }
        //printf("SIZE %d\n", (int)visited_points.size());
        // for (int i=0; i<(int)visited_points.size(); i++) {
        //     printf("%d %d %ld %d id(%d)\n", visited_points[i].a, visited_points[i].b, visited_points[i].value, visited_points[i].prev, visited_points[i].id);
        // }
        // int fd;
        // scanf("%d", &fd);
    }


    long max = 0;
    int max_id = 0;
    // printf("ORGINAl\n");
    for (int i=0; i<(int)visited_points.size(); i++) {
        // printf("%d : %d %d %d prev:(%d)\n", i, points[i].a, points[i].b, points[i].c, points[i].prev);
        if (visited_points[i].value > max) {
            max = visited_points[i].value;
            max_id = visited_points[i].id;
        }
    }
    // printf("ORGINAl END\n");

    int iter = max_id;
    while(iter != -1) {
        // printf("IT %d ", iter);
        res_points.push_back(points[iter]);
        iter = points[iter].prev;
    }
    // printf("\n");

    point point1;
    printf("%ld\n", max);
    printf("%d\n", (int)res_points.size());
    while(res_points.size() != 0) {
        point1 = res_points.back();
        res_points.pop_back();
        printf("%d %d\n", point1.a, point1.b);
    }

    return 0;
}