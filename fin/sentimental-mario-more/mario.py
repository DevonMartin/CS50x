# TODO
from cs50 import get_int

while True:
    height = get_int("Height (between 1 and 8): ")
    if height > 0 and height < 9:
        break;

for h in range(height):
    print((" " * (height - h - 1)), end="")
    print("#" * (h + 1), end="")
    print("  ", end="")
    print("#" * (h + 1))
