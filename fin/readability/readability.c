#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float count_letters(string text); // Floats are used throughout because accuracy is needed for a final calculation.
float count_words(string text);
float count_sentences(string text);
int grade_level(string text);

int main(void)
{
string text = get_string("Text: ");

grade_level(text);
}

float count_letters(string text)
{
    float letters = 0;
    int n = 0;
    int text_length = strlen(text);

    for (; n < text_length; n++)
    {
        if (isalpha(text[n]))
        {
            letters++;
        }
    }
    return letters;
}

float count_words(string text)
{
    float words = 1;
    int n = 0;
    int text_length = strlen(text);

    for (; n < text_length; n++)
    {
        if (isspace(text[n]))
        {
            words++;
        }
    }
    return words;
}

float count_sentences(string text)
{
    float sentences = 0;
    int text_length = strlen(text);

    for (int n = 0; n < text_length; n++)
    {
        if (text[n] == 33 || text[n] == 46 || text[n] == 63)
        {
            sentences++;
        }
    }
    return sentences;
}



int grade_level(string text)
{
    float L = count_letters(text) / count_words(text) * 100;
    float S = count_sentences(text) / count_words(text) * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return index;
}