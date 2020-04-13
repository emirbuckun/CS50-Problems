#include <cs50.h>
#include <stdio.h>

int get_positive_int(string prompt);

int main(void)
{
    int i = get_positive_int("Height: ");

    for (int w = 1; w <= i; w++)
    {
        for (int k = i - 1; k >= w; k--)
        {
            printf(" ");
        }
        for (int j = 1; j <= w; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
 
int get_positive_int(string prompt) 
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}

