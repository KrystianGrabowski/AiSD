#!/bin/bash
for i in {1..20}
do
printf "${i} -> "
    for j in {1..1}
    do
        python3 dataGenerator.py > tests/random${j}Test.in
    done
    ./mean
done