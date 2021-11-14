//                  ||  '||    .'|.                                  
// ... ..   ....   ...   ||  .||.     ....  .. ...     ....    ....  
//  ||' '' '' .||   ||   ||   ||    .|...||  ||  ||  .|   '' .|...|| 
//  ||     .|' ||   ||   ||   ||    ||       ||  ||  ||      ||      
// .||.    '|..'|' .||. .||. .||.    '|...' .||. ||.  '|...'  '|...' .c
//
// Author: zattak3000
// Last Update: 11/13/2021

#include <stdio.h>
#include <string.h>


void encode(char *cipher, char *plaintext, int key)
{
    int len = strlen(plaintext);

    char fence[key][len / 2];
    char idx[key];

    for (int i = 0; i < key; i++) 
    {
        idx[i] = 0;
    }
    
    char output[len];

    int i = 0;
    char r = 0;
    
    while (i < len)
    {   
        for (; r < key; r++)
        {
            if (i >= len)
            {
                i = len + 1;
                break;
            }

            fence[r][idx[r]++] = plaintext[i++];
        }
        r -= 2;

        for (; r >= 0; r--)
        {
            if (i >= len) 
            {
                i = len + 1;
                break;
            }

            fence[r][idx[r]++] = plaintext[i++];
        }
        r += 2;
    }

    char outidx = 0;

    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < idx[i]; j++)
        {
            output[outidx++] = fence[i][j];   
        }
    }

    output[outidx] = '\0';

    strcpy(cipher, output);
}

void decode(char *plaintext, char *cipher, int key)
{
    // Not quite there yet...
}

int main(int argc, char const *argv[])
{
    // Recieve user input
    char plaintext[50];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    
    int key;
    printf("Enter key: ");
    scanf("%u", &key);

    // Strip newline
    if (strchr(plaintext, '\n'))
    {
        *strchr(plaintext, '\n') = '\0';
    }

    char output[50];
    encode(output, plaintext, key);
    printf("Encrypted with key %d: %s\n", key, output);
}