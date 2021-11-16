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
#include <stdlib.h>


// Encode plaintext into ciphertext using a key
//
// @param cipher char string to write ciphertext to
// @param plaintext char string of plaintext to encode
// @param key number of rails to use during encoding
//
void encode(char *cipher, char *plaintext, int key)
{
    // Length of plaintext
    int len = strlen(plaintext);

    // 2D char array for cipher
    char **fence = (char**) malloc(sizeof(char*) * key);
    for (int i = 0; i < key; i++)
    {
        fence[i] = (char*) malloc(sizeof(char) * (len / 2));
    }
    
    // Array of counters for rails
    char *idx = (char*) malloc(sizeof(char) * key);
    for (int i = 0; i < key; i++) 
    {
        idx[i] = 0;
    }
    
    char r = 0;
    char up = 1;

    // Fill rails with plaintext
    for (int i = 0; i < len; i++)
    {
        fence[r][idx[r]++] = plaintext[i];

        // Go to next rail
        r += up ? 1 : -1;

        // Switch directions if last rail hit
        if (r == 0 || r == (key - 1))
        {
            up = !up;
        }
    }

    // Output char string
    char *output = malloc(sizeof(char) * len);
    char outidx = 0;

    // Concatenate rails into output variable
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < idx[i]; j++)
        {
            output[outidx++] = fence[i][j];   
        }
    }

    output[outidx] = '\0';

    strcpy(cipher, output);

    for (int i = 0; i < key; i++)
    {
        free(fence[i]);
    }

    free(fence);
    free(idx);
    free(output);
}

// Decode ciphertext into plaintext using a key
//
// @param plaintext char string to write plaintext
// @param cipher char string of ciphertext to decode
// @param key number of rails to use during decoding
//
void decode(char *plaintext, char *cipher, int key)
{
    // Not quite there yet...
}

int main(int argc, char const *argv[])
{
    // Plaintext to encode
    char plaintext[50];

    // Key to encode with (# or rails)
    int key;

    // Function ciphertext output
    char output[50];

    // Recieve user input
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter key: ");
    scanf("%u", &key);

    // Strip newline from plaintext
    if (strchr(plaintext, '\n'))
    {
        *strchr(plaintext, '\n') = '\0';
    }

    // Encode plaintext and print to screen
    encode(output, plaintext, key);
    printf("Encrypted with key %d: %s\n", key, output);
}