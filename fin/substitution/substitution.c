#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int convert_text();
bool first_check[26];
bool second_check();

int main(int argc, string argv[])
{
    string key = argv[1];
    if (argc == 2 && key[26] == 0 && second_check(key))
    {
        string plaintext = get_string("plaintext: ");
        convert_text(plaintext, key);
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

// Entire conversion from plaintext to ciphertext
int convert_text(string plaintext, string key)
{
    int plaintext_length = strlen(plaintext);

    // Check for a plaintext input
    if (plaintext_length == 0)
    {
        return 0;
    }

    char lowered_key[25];
    char lowered_text[plaintext_length - 1];
    char ciphertext[plaintext_length - 1];

    // Create a lowercase version of the key for consistency's sake
    for (int n = 0; n < 26; n++)
    {
        lowered_key[n] = tolower(key[n]);
    }

    // Create a lowercase version of plaintext
    for (int n = 0; n <= plaintext_length; n++)
    {
        lowered_text[n] = tolower(plaintext[n]);
    }

    // Create the ciphertext from the lowercase key and plaintext
    for (int n = 0; n <= plaintext_length; n++)
    {
        int i = lowered_text[n] - 97;
        if (plaintext[n] >= 65 && plaintext[n] <= 90)
        {
            ciphertext[n] = lowered_key[i] - 32;
        }
        else if (plaintext[n] >= 97 && plaintext[n] <= 122)
        {
            ciphertext[n] = lowered_key[i];
        }
        else
        {
            ciphertext[n] = plaintext[n];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool second_check(string key)
{
    for (int n = 0; n < 26; n++)
    {
        first_check[n] = false;
    }

    int counter = 0;
    for (int n = 0; n < 26; n++)
    {

        int i = tolower(key[n]) - 97;
        first_check[i] = true;

        if (isalpha(key[n]) == false)
        {
            return false;
        }
    }

    for (int n = 0; n < 26; n++)
    {
        if (first_check[n])
        {
            counter++;
        }
    }
    if (counter == 26)
    {
        return true;
    }
    else
    {
        return false;
    }
}