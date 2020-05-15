#!/bin/bash
for j in {1..300}
do
    python3 dataGenerator.py > tests/random${j}Test.in
done
./tester