#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

//define type name
typedef uint8_t  BYTE;
//initialize variable(block counter, return value of f read, pointers of open files and write files);
const int B_SIZE = 512;
const int FILENAME_S = 100;
int bcount = 0;
int read_r = B_SIZE;
FILE *fileopen = NULL;
FILE *imagewrite = NULL;

int main(int argc, char *argv[])
{
    //check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image/cardname.raw\n");
        return 1;
    }

    //open file for recover
    fileopen = fopen(argv[1], "r");

    //check for valid file open
    if (fileopen == NULL)
    {
        printf("Invalid File\n");
        return 2;
    }
    //Memory allocation
    char *filename = malloc(FILENAME_S);
    BYTE *buffer = malloc(B_SIZE * sizeof(BYTE));

    //read the file (512 BYTE Chunk per time)
    while (true)
    {
        //read the 512-BYTE-Chunk
        read_r = fread(buffer, sizeof(BYTE), B_SIZE, fileopen);
        //check for the end of the file
        if (read_r != B_SIZE)
        {
            break;
        }
        //check the first 4 bytes
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (bcount == 0)
            {
                //create file name and open it
                sprintf(filename, "%03i.jpg", bcount);
                imagewrite = fopen(filename, "w");
                //check valid open
                if (!imagewrite)
                {
                    return 3;
                }
                //write data into the file
                fwrite(buffer, sizeof(BYTE), B_SIZE, imagewrite);
                //increment the count
                bcount++;
            }
            else
            {
                //close(previous_image) file
                fclose(imagewrite);
                //create file name and open it
                sprintf(filename, "%03i.jpg", bcount);
                imagewrite = fopen(filename, "w");
                //check valid open
                if (!imagewrite)
                {
                    return 4;
                }
                //write data into the file
                fwrite(buffer, sizeof(BYTE), B_SIZE, imagewrite);
                //increment the count
                bcount++;
            }  
        }
        else if (bcount > 0)
        {
            //write data into the current image
            fwrite(buffer, sizeof(BYTE), B_SIZE, imagewrite);
        }
    }
    //close(files) and free(malloc)
    fclose(fileopen);
    fclose(imagewrite);
    free(buffer);
    free(filename);

    return 0;
}
