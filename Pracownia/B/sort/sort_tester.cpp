#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono> 
#include <cmath>
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
    d = opendir("sort_tests/.");
    
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
                    auto start = high_resolution_clock::now(); 
                    system((std::string("make run < sort_tests/") + p1 + ".in > sort_result.out").c_str());
                    auto stop = high_resolution_clock::now(); 
                    auto duration = duration_cast<milliseconds>(stop - start);  
                    int n;
                    point point0;
                    std::vector<point> result;
                    std::ifstream inFile;
                    std::string dummyLine, resultEmpty, includeText, fileName;
                    fileName = p1;
                    // inFile.open("sort_result.out");
                    // getline(inFile, dummyLine);
                    // while(inFile) {
                    //     inFile >> point0.x >> point0.y;
                    //     if (inFile) {
                    //         result.push_back(point0);
                    //     }
                    // }
                    // inFile.close();
                    // for (int i=0; i<result.size()-1; i++) {
                    //     if (result[i].x > result[i+1].x ) {
                    //         printf("\033[1;31mFAIL\033[0m [%s]\n", p1);
                    //         return 0;
                    //     }
                    // }
                    printf("\033[1;32mOK\033[0m [%s] (%ld)\n", p1, duration.count());
                }
            }

        }
        closedir(d);
    }
    return(0);
}