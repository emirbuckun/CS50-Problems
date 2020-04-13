#include <cs50.h>
#include <stdio.h>
#include <math.h>

int change(int cents);

float get_positive_float(string prompt);

int main(void)
{
    float amount = get_positive_float("Change owed: ");
    
    while (amount < 0);
    
    printf("%d\n", change((int)round(amount * 100)));
}

int change(int cents)
{
    return cents / 25 + (cents % 25) / 10 + ((cents % 25) % 10) / 5 + ((cents % 25) %10) % 5;
}

float get_positive_float(string prompt)
{
    float n;
    do 
    {
        n = get_float("%s", prompt);
    }
    while (n <= 0);
    return n;
}
