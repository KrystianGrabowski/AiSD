#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono> 
using namespace std::chrono; 

struct tile {
    int l;
    int m;
    int r;
};

int main(void)
{
    DIR *d;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    d = opendir("tests/.");
    
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
                    system((std::string("make run < tests/") + p1 + ".in > results.out").c_str());
                    auto stop = high_resolution_clock::now(); 
                    auto duration = duration_cast<milliseconds>(stop - start);  
                    int n;
                    tile tile0;
                    std::vector<tile> result;
                    std::ifstream inFile;
                    std::string dummyLine, resultEmpty, includeText, fileName;
                    resultEmpty = "BRAK";
                    includeText = "[brak]";
                    fileName = p1;
                    inFile.open("results.out");
                    if (fileName.find(includeText) != std::string::npos) {
                        getline(inFile, dummyLine);
                        if (dummyLine.compare(resultEmpty)) {
                            printf("\033[1;32mOK\033[0m [%s] (%ld)\n", p1, duration.count());
                        }
                        continue;
                    }
                    getline(inFile, dummyLine);
                    inFile >> n;
                    bool pathexists = true;
                    while(inFile) {
                        inFile >> tile0.l >> tile0.m >> tile0.r;
                        if (inFile) {
                            result.push_back(tile0);
                        }
                    }
                    inFile.close();
                    
                    //Sprawdzaczka poprawnosci istniejacej drogi
                    if (result.size() > 0) {
                        if (result[0].l != 0 || result[result.size()-1].r != 0) {printf("\033[1;31mFAIL\033[0m [%s]\n", p1); printf("ERROR (start, end != 0) in file %s\n", p1); return 0;}
                        for (int i=1; i<n; i++) {
                            if (result[i-1].r != result[i].l) {printf("\033[1;31mFAIL\033[0m [%s]\n", p1); printf("ERROR in file %s\n", p1); return 0;}
                        }
                    }
                    printf("\033[1;32mOK\033[0m [%s] (%ld)\n", p1, duration.count());
                }
            }

        }
        closedir(d);
    }
    return(0);
}