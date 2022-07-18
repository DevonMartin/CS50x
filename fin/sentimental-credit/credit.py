# TODO
from cs50 import get_string
from math import floor
from sys import exit

# Get cc number, put each digit in two lists, one being the reverse of the other
cc_string = get_string("Credit card number: ")
cc_int = []
cc_int_rev = []
divisor = 1
tmp = int(cc_string)
while tmp / divisor > 1:
    cc_int.append(floor(tmp / divisor % 10))
    cc_int_rev.append(floor(tmp / divisor % 10))
    divisor *= 10
cc_int.reverse()


def luhn():
    position = 0
    luhn_number = 0
    for cc_number in cc_int_rev:
        if position % 2 == 0:
            luhn_number += cc_number
        else:
            luhn_number += floor(cc_number * 2 % 10) + floor(cc_number * 2 / 10 % 10)
        position += 1
    return luhn_number % 10


def amex_check():
    i = cc_string[0] + cc_string[1]
    if (i.find("34") == 0 or i.find("37") == 0) and len(cc_string) == 15:
        print("AMEX")
        exit(0)


def mc_check():
    i = cc_string[0] + cc_string[1]
    for j in range(50, 56):
        k = f"{j}"
        if i.find(k) == 0 and len(cc_string) == 16:
            print("MASTERCARD")
            exit(0)


def visa_check():
    i = cc_string[0]
    if i == "4" and (len(cc_string) == 16 or len(cc_string) == 13):
        print("VISA")
        exit(0)


def main():
    if len(cc_string) <= 16 and luhn() == 0:
        amex_check()
        mc_check()
        visa_check()
    print("INVALID")
    exit(0)


if __name__ == "__main__":
    main()