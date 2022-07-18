#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    int score = 0;
    int n = 0;
    int wordLength = strlen(word);
    int letter;
    for (; n < wordLength; n++) // Loop running through each letter of the word. First semicolen is necessary because I'm not initializing any variables for the loop. 
    {
        letter = word[n];
        if (letter >= 65 && letter <= 90) // Scoring upper case letters
        {
            int i = letter - 65;
            score += POINTS[i];

        }
        else if (letter >= 97 && letter <= 122) // Scoring lower case letters
        {
            int i = letter - 97;
            score += POINTS[i];
        }
    }
    return score;
}
