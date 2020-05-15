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
                    int n, my_result, brute_result;
                    std::ifstream inFile;
                    std::string dummyLine, resultEmpty, includeText, fileName;
                    fileName = p1;
                    inFile.open("results.out");
                    getline(inFile, dummyLine);
                    if (!inFile) {
                        printf("\033[1;31mFAIL\033[0m [%s] No value has been returned\n", p1);
                        return 0;
                    }
                    inFile >> my_result;
                    inFile.close();
                    
                    //Sprawdzaczka brutala
                    auto start1 = high_resolution_clock::now(); 
                    system((std::string("./brute < tests/") + p1 + ".in > brute_result.out").c_str());
                    auto stop1 = high_resolution_clock::now();
                    auto duration1 = duration_cast<milliseconds>(stop1 - start1);  

                    inFile.open("brute_result.out");
                    inFile >> brute_result;
                    inFile.close();

                    if (my_result == brute_result) {
                        printf("\033[1;32mOK\033[0m [%s] time->(%ld) brute->(%ld)\n", p1, duration.count(), duration1.count());
                    }
                    else {
                        printf("\033[1;31mFAIL\033[0m [%s] Your value: [%d], Correct value: [%d]\n", p1, my_result, brute_result);
                        return 0;
                    }
                }
            }
        }
        closedir(d);
    }
    printf("\033[1;32mSUCCESS\033[0m\n");
    return(0);
}