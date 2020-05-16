from random import randint
# import argparse
# parser = argparse.ArgumentParser()
# parser.add_argument("square", help="display a square of a given number",
#                     type=int)
# args = parser.parse_args()
n = 5
m = 5
k = 5
upperBound = 5

print(f"{m} {n}")
print(f"{k}")
arr = []
for j in range(1, k+1):
    k = (randint(1, upperBound), randint(1, upperBound))
    if k in arr:
        while k in arr:
            k = (randint(1, upperBound), randint(1, upperBound))
    arr.append(k)

for j in arr:
    print(f"{j[0]} {j[1]} {randint(1, upperBound)}")

