#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LENGTH 45
#define ASCIIa 97
#define APOSTR 26
#define ALPHABET 27

typedef struct node
{
   bool is_word;
   struct node* array[ALPHABET];
}
node;

//Global variables
node* root;

//Prototypes
node* checkalloc (node* pointer, char c);
unsigned int iterate (node* pointer);
bool check (const char* word);

int main (int argc, char* argv[]) {
    //Root
    root = malloc(sizeof(node));
    root -> is_word = false;

    //Initialise the elements of the array to NULL
    for(int i = 0; i < ALPHABET; i++)
    {
        root -> array[i] = NULL;
    };



    //Open dictionary                           CHANGE THIS!!
    FILE* dict = fopen(argv[argc - 1], "r");

    //Checking success
    if (dict == NULL)
    {
        printf("Fail to open file \n");
        return 1;                               //CHANGE THIS!!
    };


    char buffer;
    node* trav = root;

    //Iterates the file and creates nodes
    while (fread(&buffer, sizeof(char), 1, dict) == 1)
    {
        trav = checkalloc(trav, buffer);
    }
    fclose(dict);


    printf("%x \n", iterate(root));

    printf("%d \n", check("a"));

}

//Checkalloc with a pointer and a char, checks if in that node the char exist, returning the pointer for the next node where the char
//exists or creating a node and returning the node's pointer
node* checkalloc (node* pointer, char c)
{
    //We hit the end of the word
    if (c == '\n')
    {
        //We register the end of the word
        pointer -> is_word = true;
        //go back to the root
        return root;
    }
    else
    {
        //Translate char to array position
        int position = (isalpha(c)) ? c - ASCIIa : APOSTR;

        //Case node doesn't exist
        if(pointer -> array[position] == NULL)
        {
            //create node and initialise it
            pointer -> array[position] = malloc(sizeof(node));
            pointer -> array[position] -> is_word = false;
            for (int i = 0; i < ALPHABET; i++)
            {
                pointer -> array[position] -> array[i] = NULL;
            };

            return pointer -> array[position];
        }
        //Case node already exists
        else
        {
            return pointer -> array[position];
        }
    }
}

//Size

unsigned int iterate (node* pointer){

    int counter = 0;

    counter = (pointer -> is_word == true) ? counter + 1 : counter;

    for (int i = 0; i < ALPHABET; i++)
    {
        if (pointer -> array [i] != NULL)
        {
            counter += iterate(pointer -> array[i]);
        }
    }
    return counter;

}

bool check (const char* word)
{
    node* trav = root;
    int position;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        position = (isalpha(word[i])) ? word[i] - ASCIIa : APOSTR;

        if (trav -> array[position] != NULL)
        {
            if (trav -> array[position] -> is_word && i == n - 1)
            {
                return true;
            }
            else
            {
                trav = trav -> array[position];
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}