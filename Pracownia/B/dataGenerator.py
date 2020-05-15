from random import randint
# import argparse
# parser = argparse.ArgumentParser()
# parser.add_argument("square", help="display a square of a given number",
#                     type=int)
# args = parser.parse_args()
number = 10000000
numberOfValues = 500000

# print("%s" % args.square);
print("%s" % numberOfValues);
for j in range(numberOfValues):
    print(f"{randint(0, number)} {randint(0, number)}")