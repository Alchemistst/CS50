/*Vigenere Cipher:
1) Takes argument as a key.
2) Prompts the user for imput of text to cipher.
3) Returns a ciphered text.
*/

//Libraries
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Functions
char swap(char letter, char key);
int toAlpha(char letter);
int toASCII(char letter, bool lowerCase);

int main(int argc, string argv[])
{
    //Checking that the number of args match what we expect
    string key = argv[argc - 1];
    bool validKey = true;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            validKey = false;
        };
    }
    if (argc == 2 && validKey)
    {
        //Prompt the user
        string plaintext = get_string("plaintext: ");


        //Delivering answer
        printf("ciphertext: ");
        //Looping through the string
        for (int i = 0, n = strlen(plaintext), j = 0; i < n; i++, j++)
        {
            if (j == strlen(key))
                //To make sure we don't surpass the key's length and we keep looping through it
            {
                j = 0;
            }

            if (isalpha(plaintext[i]))
                //Checking if it's a letter
            {
                printf("%c", swap(plaintext[i], key[j]));
            }
            else
                //If not's a letter, print it straigh away, but substract 1 from the counter so it doesn't advance key
            {
                printf("%c", plaintext[i]);
                j--;
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./vigenere k \n");
        return 1;
    }
}

//Function that takes a char and the key and swaps the char following Vigenere's algorithm
char swap(char letter, char key)
{
    return (char)toASCII((toAlpha(letter) + toAlpha(key)) % 26, islower(letter));
}

//Function to convert to alphabetial index
int toAlpha(char letter)
{
#define A_LOWER_ASCII 97
#define A_CAPS_ASCII 65

    int letterNum = (int) letter;

    if (islower(letter))
    {
        return letterNum - A_LOWER_ASCII;
    }
    else
    {
        return letterNum - A_CAPS_ASCII;

    }
}
//Function to convert to ASCII index
int toASCII(char letter, bool lowerCase)
{
#define A_LOWER_ASCII 97
#define A_CAPS_ASCII 65

    int letterNum = (int) letter;

    if (lowerCase)
    {
        return letterNum + A_LOWER_ASCII;
    }
    else
    {
        return letterNum + A_CAPS_ASCII;
    }
}