#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
                while (i == strlen(argv[1]) - 1)
                {
                    int key = atoi(argv[1]);
                    string t = get_string("plaintext: ");
                    printf("ciphertext: ");
                    for (int j = 0; j < strlen(t); j++)
                    {
                        if (islower(t[j]))
                        {
                            printf("%c", (t[j] - 'a' + key) % 26 + 'a');
                        }
                        else if (isupper(t[j]))
                        {
                            printf("%c", (t[j] - 'A' + key) % 26 + 'A');
                        }
                        else
                        {
                            printf("%c", t[j]);
                        }
                    }
                    printf("\n");
                    
                    return 0;
                }
            }
            else 
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    
    else 
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
