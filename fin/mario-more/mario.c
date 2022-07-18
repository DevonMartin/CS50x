#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = get_int("How tall is the pyramid? ");
    int spaces;
    string block = "#";
    int blocksonthisrow = 1;
    int blockstobuild;

    while (height < 1 || height > 8) 
        height = get_int("The pyramid must be 8 blocks tall or shorter! How tall is it? ");

    while (height >= 1 && height <= 8) { // A loop to make a new line after each line is created by other loops.

        for (spaces = height - 1; spaces > 0; spaces--) // Calculate and print spaces needed on left side of pyramid.
            printf(" ");

        for (blockstobuild = blocksonthisrow; blockstobuild > 0; blockstobuild--) // Calculate and print blocks needed on left side.
            printf("%s", block);

        printf("  "); // Space out left and right blocks.

        for (blockstobuild = blocksonthisrow; blockstobuild >= 1; blockstobuild--) // Calculate and print blocks needed on right side. Repetative; better method?
            printf("%s", block);

        printf("\n");

        height--;
        blocksonthisrow++;
    }
}