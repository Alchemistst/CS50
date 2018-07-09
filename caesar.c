/*Caesar Cipher:
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
char swap(char letter, int key);

int main(int argc, string argv[])
{
    //Checking that the number of args match what we expect
    if (argc == 2)
    {
        //Prompt the user
        string plaintext = get_string("plaintext: ");
        int key = atoi(argv[argc - 1]); //Getting the key and turning it into an int
        //Delivering answer
        printf("ciphertext: ");
        //Looping through the string
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            printf("%c", swap(plaintext[i], key));
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar k \n");
        return 1;
    }
}

//Function that takes a char and the key and swaps the char to the keyth char
char swap(char letter, int key)
{
#define A_LOWER_ASCII 97
#define A_CAPS_ASCII 65
#define NUM_LETTERS_ALPH 26

    if (isalpha(letter))
    {
        //if it's a letter we apply the key
        int letterNum = (int) letter;

        if (islower(letter))
        {
            letterNum -= A_LOWER_ASCII;
            return (char)(letterNum + key) % NUM_LETTERS_ALPH + A_LOWER_ASCII;
        }
        else
        {
            letterNum -= A_CAPS_ASCII;
            return (char)(letterNum + key) % NUM_LETTERS_ALPH + A_CAPS_ASCII;
        }
    }
    else
    {
        //if not, the char remains the same
        return letter;
    }
}