//Sets up C language to handle "Standard Inputs and Outputs"
#include <stdio.h>
//Sets up C language to use commands created by CS50, for ease of use in the class
#include <cs50.h>

//Creates the body of the application. main returns an integer and takes no input.
int main(void)
{
    string name = get_string("What's your name? ");
    printf("hello, %s\n", name);
}