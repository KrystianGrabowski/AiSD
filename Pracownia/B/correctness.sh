#!/bin/bash
for j in {1..20}
do
    python3 dataGenerator.py > tests/random${j}Test.in
done
./tester