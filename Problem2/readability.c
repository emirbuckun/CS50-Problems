#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string t = get_string("Text: ");
    int i;
    float L = 0, S = 0, index = 0, letters = 0, words = 0, sentences = 0;
    for (i = 0; i < strlen(t); i++)
    {
        if ((t[i] >= 'a' && t[i] <= 'z') || (t[i] >= 'A' && t[i] <= 'Z'))
        {
            letters++;
        }
        if (t[i] == ' ')
        {
            words++;
        }
        if (t[i] == '.' || t[i] == '?' || t[i] == '!')
        {
            sentences++;
        }
    }
    L = letters * 100 / (words + 1);
    S = sentences * 100 / (words + 1);
    index = 0.0588 * L - 0.296 * S - 15.8;
    
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}
