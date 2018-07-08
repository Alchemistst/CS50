#include <stdio.h>
#include <cs50.h>
//WELLCOME to CREDIT: It'll ask you for your card number and it'll chack if that card number is correct. It'll also give you the company name!! (as long as is VISA, AMEX or MASTERCARD)
//Disclaimer:
//This implementations is done just by using the concepts already seen in week 1 of cs50. Functions, boleans or library functions weren't used, although the code could have been more efficient with them.

int main(void)
{
    //VARIABLES
    long long cardN = 0;
    int i = 0;
    int current = 0;
    int previous = 0;
    int checksum = 0;


    //PROMPTING THE USER
    do
    {
        cardN = get_long_long("Number: ");
        //PERFORM THE CHECKSUM
        //SEGMENTING THE NUMBER
        while (cardN > 0)
        {
            previous = current; //Stores the last number from the previous loop run.
            current = cardN % 10; //This segments the last digit from the card number


            //Alternate between every other number
            if (i % 2 == 0)
            {
                //Numbers that are simply added
                checksum = checksum + current;
            }
            else
            {
                //Number that are multiplied by 2
                if (current >= 5)
                {
                    //If more than one digit after multiplied by 2, add those two digits
                    checksum = checksum + (current * 2) % 10 + ((current * 2) % 100 - (current * 2) % 10) / 10;
                }
                else
                {
                    //Otherwise, just add them to the total checksum straight away after the product
                    checksum = checksum + current * 2;
                }
            }
            //updating counters
            cardN = cardN / 10; //truncate the card number's last digit
            i++;
        }
    }
    while (cardN < 0);

    //CHECKING IF THE CHECKSUM IS CORRECT
    if (checksum % 10 == 0)
    {
        //Idetifying the company and making sure it fits the number of digits for each company
        switch (current * 10 + previous)
        {
            case 34:
            case 37:
                if (i == 15)
                {
                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            case 51 ... 55 :
                if (i == 16)
                {
                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            case 40 ... 49 :
                if (i == 16 || i == 13)
                {
                    printf("VISA\n");
                }
                else
                {
                    printf("INVALID\n");
                }
                break;

            //In case we don't knowthe name of the company
            default:
                printf("INVALID\n");
        }
    }
    else
    {
        //If the checksum is incorrect
        printf("INVALID\n");
    }
}