#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if ((argc == 2) && (strlen(argv[1]) == 26))
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isalpha(argv[1][i]))
            {
                for (int j = i + 1; argv[1][j] != '\0'; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        {
                            printf("Key must not contain repeated characters.\n");
                            return 1;
                        }
                    }
                }
            }
            else
            {
                printf("Key must only contain alphabetic characters\n");
                return 1;
            }
        }
        string t = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int k = 0; k < strlen(t); k++)
        {
            if (islower(t[k]))
            {
                int q = t[k] - 'a';
                printf("%c", tolower(argv[1][q]));
            }
            else if (isupper(t[k]))
            {
                int w = t[k] - 'A';
                printf("%c", toupper(argv[1][w]));
            }
            else
            {
                printf("%c", t[k]);
            }
        }
        printf("\n");
    }
    
    else if ((argc == 2) && (strlen(argv[1]) != 26))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else 
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
