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
    std::map<int, point> x_array;

    std::vector<point> res_points;
    std::vector<point> points;
    std::vector<point> level_points;

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
        x_array.insert(std::pair<int, point>(-1, point_start ));
    }

    int current_y = 1;
    int iter_y = 0;

    long max_val = 0;
    int max_id = 0;
    
    // Fill first row using cost
    while (iter_y < k && points[iter_y].b == current_y) {
        if (iter_y+1 < k && points[iter_y+1].b == current_y) {
            points[iter_y+1].value = points[iter_y].value + points[iter_y+1].c;
            points[iter_y+1].prev = points[iter_y].id;
        }
        if (points[iter_y].value > max_val) {
            max_val = points[iter_y].value;
            max_id = points[iter_y].id;
        }
        x_array[points[iter_y].a] =  points[iter_y];
        iter_y++;
    }


    while (iter_y < k) {
        current_y = points[iter_y].b;
        //printf("POINTS\n");
        while (current_y == points[iter_y].b && iter_y < k) {
            //printf("%d %d\n", points[iter_y].a, points[iter_y].b);
            level_points.push_back(points[iter_y++]);
            
        }
        //printf("POINTS\n");

        for (int i=0; i<(int)level_points.size(); i++) {
            // Find first smaller or equal element in the array
            auto pointer = x_array.lower_bound(level_points[i].a);
            if (pointer != x_array.begin() && pointer->first != level_points[i].a) pointer--;
            if (pointer == x_array.end()) {
                pointer--;
            }

            if (i != 0) {
                if (pointer->second.value > level_points[i-1].value) {
                    level_points[i].value = pointer->second.value + level_points[i].c;
                    points[level_points[i].id].prev = pointer->second.id;
                    level_points[i].prev = pointer->second.id;
                }
                else {
                    level_points[i].value = level_points[i-1].value + level_points[i].c;
                    points[level_points[i].id].prev = level_points[i-1].id;
                    level_points[i].prev = level_points[i-1].id;
                }
            }
            else {
                level_points[i].value = pointer->second.value + level_points[i].c;
                points[level_points[i].id].prev = pointer->second.id;
                level_points[i].prev = pointer->second.id;

            }  
        }

        for (int i=0; i<(int)level_points.size(); i++) {
            if (max_val < level_points[i].value) {
                max_val = level_points[i].value;
                max_id = level_points[i].id;
            }
            x_array[level_points[i].a] = level_points[i];
            auto it_elem = x_array.find(level_points[i].a);
            auto it_start = it_elem;
            auto it_helper = it_elem;
            it_helper++;
            int mx = it_elem->second.value;

            if (it_elem != x_array.end()) {
                if (it_helper != x_array.end() && it_helper->second.value < mx) {
                    it_elem++;
                }
                
                while(it_elem != x_array.end() && it_elem->second.value < mx) {
                    //printf("USUWAM\n");
                    it_elem++;
                }
                if (it_elem != it_start) {
                    //printf("DEL -> %d ", it_elem == x_array.end());
                    x_array.erase ( ++it_start, it_elem ); 
                }
            }

        }

        level_points.clear();

        // printf("BEFORE DEL SIZE: %d\n", (int)x_array.size());
        // for(auto iewt = x_array.begin(); iewt != x_array.end(); ++iewt)
        // {
        //     printf("%d %d %d prev(%d) id(%d) val(%ld)\n", iewt->second.a, iewt->second.b, iewt->second.c,  iewt->second.prev, iewt->second.id, iewt->second.value);
        // }
        // int fd;
        // scanf("%d", &fd);
    }

    int iter = max_id;
    while(iter != -1) {
        res_points.push_back(points[iter]);
        iter = points[iter].prev;
    };

    point point1;
    printf("%ld\n", max_val);
    printf("%d\n", (int)res_points.size());
    while(res_points.size() != 0) {
        point1 = res_points.back();
        res_points.pop_back();
        printf("%d %d\n", point1.a, point1.b);
    }

    return 0;
}