#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // repeating over each raw
    for (int h = 0; h < height; h++)
    {
        // repeating for each pixel in the raw
        for (int w = 0; w < width; w++)
        {
            // calculating the average value
            int average = round(((float)image[h][w].rgbtRed + (float)image[h][w].rgbtGreen + (float)image[h][w].rgbtBlue) / 3);
            // assign RGB values to the average value
            image[h][w].rgbtRed = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // calculating the sepia values for each colour value
            float sepiared = 0.393 * image[h][w].rgbtRed + 0.769 * image[h][w].rgbtGreen + 0.189 * image[h][w].rgbtBlue;
            float sepiagreen = 0.349 * image[h][w].rgbtRed + 0.686 * image[h][w].rgbtGreen + 0.168 * image[h][w].rgbtBlue;
            float sepiablue = 0.272 * image[h][w].rgbtRed + 0.534 * image[h][w].rgbtGreen + 0.131 * image[h][w].rgbtBlue;
            sepiared = round(sepiared);
            sepiagreen = round(sepiagreen);
            sepiablue = round(sepiablue);

            // assign RGB values to the sepia values
            image[h][w].rgbtRed = (sepiared <= 255) ? sepiared : 255;
            image[h][w].rgbtGreen = (sepiagreen <= 255) ? sepiagreen : 255;
            image[h][w].rgbtBlue = (sepiablue <= 255) ? sepiablue : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        // creating an array to copy the original data
        RGBTRIPLE *copy = malloc(width * sizeof(RGBTRIPLE));
        if (copy == NULL)
        {
            return;
        }
        // coping the origanal raw in the new array
        for (int w = 0; w < width; w++)
        {
            copy[w].rgbtRed = image[h][w].rgbtRed;
            copy[w].rgbtGreen = image[h][w].rgbtGreen;
            copy[w].rgbtBlue = image[h][w].rgbtBlue;
        }
        // reflect the raw in the original array
        for (int c = 0; c < width; c++)
        {
            image[h][c].rgbtRed = copy[width - c - 1].rgbtRed;
            image[h][c].rgbtGreen = copy[width - c - 1].rgbtGreen;
            image[h][c].rgbtBlue = copy[width - c - 1].rgbtBlue;
        }
        // free space
        free(copy);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the image
    RGBTRIPLE copy[height][width];
    
    // repeating for each raw
    for (int h = 0; h < height; h++)
    {
        // repeating for each colum
        for (int w = 0; w < width; w++)
        {
            //calculating the avaerage color value for each pixel through total variables
            float tred = 0;
            float tgreen = 0;
            float tblue = 0;
            int pnum = 0;
            int rowcord [] = {h - 1, h, h + 1};
            int colcord [] = {w - 1, w, w + 1};
            //repeating for each pixel grid
            for (int n = 0; n < 3; n++)
            {
                for (int m = 0; m < 3; m++)
                {
                    int currentr = rowcord[n];
                    int currentc = colcord[m];
                    //checking if the pixel is inside the image or not
                    if ((currentr >= 0) && (currentr < height) && (currentc >= 0) && (currentc < width))
                    {
                        RGBTRIPLE currentp = image[currentr][currentc];
                        tred += currentp.rgbtRed;
                        tgreen += currentp.rgbtGreen;
                        tblue += currentp.rgbtBlue;
                        //calculate how many pixel in the grid for the corner and edge cases through num
                        pnum += 1;
                    }
                }
            }
            //assign the pixel color values to the average value
            copy[h][w].rgbtRed = round(tred / pnum);
            copy[h][w].rgbtGreen = round(tgreen / pnum);
            copy[h][w].rgbtBlue = round(tblue / pnum);
        }
    }
    //rewrite the original image
    for (int i = 0; i < height; i++)
    {
        for (int l = 0; l < width; l++)
        {
            image[i][l] = copy[i][l];
        }
    }
    return;
}
