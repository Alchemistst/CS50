// Copies a BMP file
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAT32_size 512
#define LENGTH_OF_FILE_NAME 7

typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        //Wrong input
        fprintf(stderr, "Usage: ./recover file.raw \n");
        return 1;
    }

    //Reading arguments
    char *file_name = argv[argc - 1];

    //Open input file to read
    FILE *memory = fopen(file_name, "r");

    //Parameters for reading/writting
    bool isOpen = false;
    int counter = 0;
    BYTE byteBuffer[FAT32_size];
    FILE *img = NULL;
    char imgName[LENGTH_OF_FILE_NAME];

    //Scan 512 bytes at a time
    while (fread(byteBuffer, sizeof(byteBuffer), 1, memory) == 1)
    {
        //Check the first 4 bytes
        if (byteBuffer[0] == 0xff && byteBuffer[1] == 0xd8 && byteBuffer[2] == 0xff && byteBuffer[3] >= 0xe0 && byteBuffer[3] <= 0xef)
        {
            //Close any img files already open
            if (isOpen)
            {
                fclose(img);
            }

            printf("Found a new JPEG \n");
            sprintf(imgName, "%03i.jpg", counter);
            printf("%s \n", imgName);
            //Create a new image
            img = fopen(imgName, "w");
            counter ++;
            isOpen = true;
            fwrite(byteBuffer, sizeof(byteBuffer), 1, img);
        }
        else if (isOpen)
        {
            //Continue writting if there's an open img already
            fwrite(byteBuffer, sizeof(byteBuffer), 1, img);
        }
    }
    //Closing reading and writing files
    fclose(memory);
    fclose(img);

    printf("This amount of pics: %i \n", counter);
    printf("You pretty people! \n");
}
