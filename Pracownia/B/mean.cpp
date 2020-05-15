#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono> 
#include <cmath>
#include <unistd.h>
using namespace std::chrono; 

struct point {
    int x;
    int y;
};

int main(void)
{
    DIR *d;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    d = opendir("tests/.");
    int counter = 0;
    int64_t total = 0; 
    
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            p1=strtok(dir->d_name,".");
            p2=strtok(NULL,".");
            if(p2!=NULL)
            {
                ret=strcmp(p2,"in");
                if(ret==0)
                {
                    counter++;
                    auto start = high_resolution_clock::now(); 
                    system((std::string("make run < tests/") + p1 + ".in > results.out").c_str());
                    auto stop = high_resolution_clock::now(); 
                    auto duration = duration_cast<milliseconds>(stop - start);  
                    int n;
                    point point0;
                    std::vector<point> result;
                    std::ifstream inFile;
                    std::string dummyLine, resultEmpty, includeText, fileName;
                    fileName = p1;
                    inFile.open("results.out");
                    getline(inFile, dummyLine);
                    while(inFile) {
                        inFile >> point0.x >> point0.y;
                        if (inFile) {
                            result.push_back(point0);
                        }
                    }
                    inFile.close();
                    
                    //Sprawdzaczka obwodu znalezionego trójkąta
                    if (result.size() != 3) {
                        printf("\033[1;31mFAIL\033[0m [%s] Wrong number of points\n", p1);
                        return 0;
                    }
                    
                    double d1, d2, d3, perimeter;
                    d1 = sqrt( pow(result[0].x - result[1].x, 2 ) + pow(result[0].y - result[1].y, 2 ));
                    d2 = sqrt( pow(result[0].x - result[2].x, 2 ) + pow(result[0].y - result[2].y, 2 ));
                    d3 = sqrt( pow(result[2].x - result[1].x, 2 ) + pow(result[2].y - result[1].y, 2 ));
                    perimeter = d1 + d2 + d3;
                    

                    double bruteforce;
                    // auto start1 = high_resolution_clock::now(); 
                    // system((std::string("./brute < tests/") + p1 + ".in > brute_result.out").c_str());
                    // auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration;  

                    // inFile.open("brute_result.out");
                    // inFile >> bruteforce;
                    bruteforce = perimeter;
                    total += duration.count();
                }
            }
        }
        closedir(d);
    }
    printf("\033[1;32mOK\033[0m [%ld] \n", total/counter);
    return(0);
}