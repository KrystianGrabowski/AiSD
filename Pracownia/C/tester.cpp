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



const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}


int main(void)
{
    DIR *d;
    char *p1,*p2;
    int ret;
    struct dirent *dir;
    d = opendir("in/.");
    
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
                    system((std::string("make run < in/") + p1 + ".in > results.out").c_str());
                    auto stop = high_resolution_clock::now(); 
                    auto duration = duration_cast<milliseconds>(stop - start);  
                    int n;
                    std::ifstream inFile;
                    std::string dummyLine, resultEmpty, includeText, fileName;
                    fileName = p1;
                    inFile.open("results.out");
                    getline(inFile, dummyLine);
                    std::string answer, min_val, min_coins, max_val, max_coins;
                    std::string yes_answer = "TAK";
                    inFile >> answer;
                    if (answer == yes_answer) {
                        inFile >> min_val;
                        getline(inFile, min_coins);
                        min_coins = trim(min_coins);
                        inFile >> max_val;
                        getline(inFile, max_coins);
                        max_coins = trim(max_coins);
                    }
                    inFile.close();

                    std::string out_answer, out_min_val, out_min_coins, out_max_val, out_max_coins;
                    inFile.open(std::string("out/") + p1 + ".out");
                    inFile >> out_answer;
                    if (out_answer == yes_answer) {
                        inFile >> out_min_val;
                        getline(inFile, out_min_coins);
                        out_min_coins = trim(out_min_coins);
                        inFile >> out_max_val;
                        getline(inFile, out_max_coins);
                        out_max_coins = trim(out_max_coins);
                    }

                    if (answer == out_answer) {
                        if (answer == yes_answer) {
                            if (min_val != out_min_val) {
                                printf("\033[1;31mFAIL\033[0m [%s] Your value:[%s] Correct value: [%s] (mininum value)\n", p1, min_val.c_str() , out_min_val.c_str());
                                return 0;         
                            }
                            if (min_coins != out_min_coins) {
                                printf("\033[1;31mFAIL\033[0m [%s] Your value:[%s] Correct value: [%s] (mininum coins)\n", p1, min_coins.c_str() , out_min_coins.c_str());
                                return 0;         
                            }
                            if (max_val != out_max_val) {
                                printf("\033[1;31mFAIL\033[0m [%s] Your value:[%s] Correct value: [%s] (maximum value)\n", p1, max_val.c_str() , out_max_val.c_str());
                                return 0;         
                            }
                            if (max_coins != out_max_coins) {
                                printf("\033[1;31mFAIL\033[0m [%s] Your value:[%s] Correct value: [%s] (maximum coins)\n", p1, max_coins.c_str() , out_max_coins.c_str());
                                return 0;         
                            }
                        }
                        printf("\033[1;32mOK\033[0m [%s] time->(%ld)\n", p1, duration.count());
                    }
                    else {
                        printf("\033[1;31mFAIL\033[0m [%s] Your value:[%s] Correct value: [%s]\n", p1, answer.c_str(), out_answer.c_str());
                        return 0;
                    }
                }
            }
        }
        closedir(d);
    }
    return(0);
}