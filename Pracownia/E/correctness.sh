#!/bin/bash
for j in {1..20000}
do
    python3 dataGenerator.py > tests/random${j}Test.in
done
./tester