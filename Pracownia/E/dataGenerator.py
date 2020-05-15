from random import randint
# import argparse
# parser = argparse.ArgumentParser()
# parser.add_argument("square", help="display a square of a given number",
#                     type=int)
# args = parser.parse_args()
number = 200
upperBound = 10000
element = randint(1, number)

# print("%s" % args.square);
print("%s %s" % (number, element))
for j in range(1, number+1):
    print(f"{randint(0, upperBound)}")

