#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long cardnumber = get_long("What is your credit card number? ");

    // Establish a variable for each digit of the card number. "Invalid" exists to ensure number is not too big.
    long n0 = cardnumber % 10;
    long n1 = (cardnumber / 10) % 10;
    long n2 = (cardnumber / 100) % 10;
    long n3 = (cardnumber / 1000) % 10;
    long n4 = (cardnumber / 10000) % 10;
    long n5 = (cardnumber / 100000) % 10;
    long n6 = (cardnumber / 1000000) % 10;
    long n7 = (cardnumber / 10000000) % 10;
    long n8 = (cardnumber / 100000000) % 10;
    long n9 = (cardnumber / 1000000000) % 10;
    long n10 = (cardnumber / 10000000000) % 10;
    long n11 = (cardnumber / 100000000000) % 10;
    long n12 = (cardnumber / 1000000000000) % 10;
    long n13 = (cardnumber / 10000000000000) % 10;
    long n14 = (cardnumber / 100000000000000) % 10;
    long n15 = (cardnumber / 1000000000000000) % 10;
    long invalid = (cardnumber / 10000000000000000) % 10;

    // Manipulate every other CC number according to Luhn's Algorithm of doubling and adding digits of the sum.
    // ** Repetitive. Add n even variables to an array and cycle each variable through one formula. **
    long n1luhn = ((n1 * 2 % 10) + (n1 * 2 / 10 % 10));
    long n3luhn = ((n3 * 2 % 10) + (n3 * 2 / 10 % 10));
    long n5luhn = ((n5 * 2 % 10) + (n5 * 2 / 10 % 10));
    long n7luhn = ((n7 * 2 % 10) + (n7 * 2 / 10 % 10));
    long n9luhn = ((n9 * 2 % 10) + (n9 * 2 / 10 % 10));
    long n11luhn = ((n11 * 2 % 10) + (n11 * 2 / 10 % 10));
    long n13luhn = ((n13 * 2 % 10) + (n13 * 2 / 10 % 10));
    long n15luhn = ((n15 * 2 % 10) + (n15 * 2 / 10 % 10));

    // Evens and odds separated for readibility.
    long luhnodds = (n0 + n2 + n4 + n6 + n8 + n10 + n12 + n14);
    long luhnevens = (n1luhn + n3luhn + n5luhn + n7luhn + n9luhn + n11luhn + n13luhn + n15luhn);
    long luhn = ((luhnodds + luhnevens) % 10);

    if (invalid != 0 || luhn != 0) // Make sure number is 16 digits or less and that Luhn's Algorithm works
    {
        printf("INVALID\n");
    }
    else if (n15 == 0 && n14 == 3 && (n13 == 4 || n13 == 7)) // Check AmEx conditions
    {
        printf("AMEX\n");
    }
    else if (n15 == 5 && (n14 == 1 || n14 == 2 || n14 == 3 || n14 == 4 || n14 == 5)) // Check MasterCard conditions
    {
        printf("MASTERCARD\n");
    }
    else if (n15 == 4 || (n15 == 0 && n14 == 0 && n13 == 0 && n12 == 4)) // Check Visa conditions
    {
        printf("VISA\n");
    }
    else // If the number technically works as a credit card number but doesn't fit into any CC provider's rules, it must be invalid.
    {
        printf("INVALID\n");
    }
}