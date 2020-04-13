#include <stdio.h>
#include <cs50.h>

void card_brand(long ccn);
bool checksum(long ccn, int len);
bool checklenght(int len);
int lenght(long n);
void check_validity(long ccn);
int get_longer_long(string prompt);

int main(void)
{
    long long number = get_long_long("Number: ");
    check_validity(number);
}

void check_validity(long ccn)
{
    int len = lenght(ccn);
    if (!(checklenght(len)) || !(checksum(ccn, len)))
    {
        printf("INVALID\n");
        return;
    }

    card_brand(ccn);
}

int lenght(long n)
{
    int len = 0;
    while (n > 0)
    {
        len++;
        n /= 10;
    }
    return len;    
}

bool checklenght(int len)
{
    if (len == 13 || len == 15 || len == 16)
        return true;
    return false;
}

bool checksum(long ccn, int len)
{
    int sum = 0;
    for (int i = 0; i < len; i++, ccn /= 10)
    {
        if (i % 2 == 0)
        {
            sum += (ccn % 10);
        }
        else 
        {
            int digit = (2 * (ccn % 10));
            sum += (digit / 10 + digit % 10);
        }
    }
    if (sum % 10 == 0)
        return true;
    return false;
    
}   

void card_brand(long ccn)
{
    if ((ccn >= 340000000000000 && ccn < 350000000000000) || (ccn >= 370000000000000 && ccn < 380000000000000))
    {
        printf("AMEX\n");
    }
    else if ((ccn >= 5100000000000000 && ccn < 5600000000000000))
    {
        printf("MASTERCARD\n");
    }
    else if ((ccn >= 4000000000000000 && ccn < 5000000000000000) || (ccn >= 4000000000000 && ccn < 5000000000000)) 
    {
        printf("VISA\n");        
    }
    else
    {
        printf("INVALID\n"); 
    }   
}

int get_longer_long(string prompt)
{
    long n;
    do
    {
        n = get_long_long("%s", prompt);
    }
    while (n <= 0);
    return n;
}
