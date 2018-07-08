#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //VARIABLES
    int n;

    //PORMPTING THE USER
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);

    //DRAWING LOOPS
    //LOOP FOR ROWS
    for (int i = 0; i < n; i++)
    {
        //LOOP FOR SPACES
        for (int j = n - i - 1; j > 0; j--)
        {
            printf(" ");
        };

        //LOOP FOR #
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        //GAP
        printf("  ");

        //LOOP FOR #
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        //NEW LINE
        printf("\n");
    }
}