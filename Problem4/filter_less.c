#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            int average = round(sum / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed[height][width];
    int tempGreen[height][width];
    int tempBlue[height][width];
    
    //creating temp colors
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            tempRed[a][b] = image[a][b].rgbtRed;
            tempGreen[a][b] = image[a][b].rgbtGreen;
            tempBlue[a][b] = image[a][b].rgbtBlue;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            //for left-top corner
            if (i == 0 && j == 0)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i + 1][j] + tempRed[i + 1][j + 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j + 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j + 1];
                
                int averageRed = round(sumRed / 4);
                int averageGreen = round(sumGreen / 4);
                int averageBlue = round(sumBlue / 4);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for right-top corner
            if (i == 0 && j == width - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j - 1] + tempRed[i + 1][j] + tempRed[i + 1][j - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j - 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j - 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j - 1];
                
                int averageRed = round(sumRed / 4);
                int averageGreen = round(sumGreen / 4);
                int averageBlue = round(sumBlue / 4);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for left-bottom corner
            if (i == height - 1 && j == 0)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i - 1][j] + tempRed[i - 1][j + 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i - 1][j] + tempGreen[i - 1][j + 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i - 1][j] + tempBlue[i - 1][j + 1];
                
                int averageRed = round(sumRed / 4);
                int averageGreen = round(sumGreen / 4);
                int averageBlue = round(sumBlue / 4);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for right-bottom corner
            if (i == height - 1 && j == width - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j - 1] + tempRed[i - 1][j] + tempRed[i - 1][j - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j - 1] + tempGreen[i - 1][j] + tempGreen[i - 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j - 1] + tempBlue[i - 1][j] + tempBlue[i - 1][j - 1];
                
                int averageRed = round(sumRed / 4);
                int averageGreen = round(sumGreen / 4);
                int averageBlue = round(sumBlue / 4);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for first row
            if (i == 0 && j != 0 && j != width - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i + 1][j] + tempRed[i + 1][j + 1] + tempRed[i][j - 1] + tempRed[i + 1][j - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j + 1] + tempGreen[i][j - 1] + tempGreen[i + 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j + 1] + tempBlue[i][j - 1] + tempBlue[i + 1][j - 1];
                
                int averageRed = round(sumRed / 6);
                int averageGreen = round(sumGreen / 6);
                int averageBlue = round(sumBlue / 6);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for first column
            if (j == 0 && i != 0 && i != height - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i + 1][j] + tempRed[i + 1][j + 1] + tempRed[i - 1][j] + tempRed[i - 1][j + 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j + 1] + tempGreen[i - 1][j] + tempGreen[i - 1][j + 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j + 1] + tempBlue[i - 1][j] + tempBlue[i - 1][j + 1];
                
                int averageRed = round(sumRed / 6);
                int averageGreen = round(sumGreen / 6);
                int averageBlue = round(sumBlue / 6);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for last row
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i - 1][j] + tempRed[i - 1][j + 1] + tempRed[i][j - 1] + tempRed[i - 1][j - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i - 1][j] + tempGreen[i - 1][j + 1] + tempGreen[i][j - 1] + tempGreen[i - 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i - 1][j] + tempBlue[i - 1][j + 1] + tempBlue[i][j - 1] + tempBlue[i - 1][j - 1];
                
                int averageRed = round(sumRed / 6);
                int averageGreen = round(sumGreen / 6);
                int averageBlue = round(sumBlue / 6);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for last column
            if (j == width - 1 && i != 0 && i != height - 1)
            {
                float sumRed = tempRed[i][j] + tempRed[i + 1][j] + tempRed[i - 1][j] + tempRed[i + 1][j - 1] + tempRed[i][j - 1] + tempRed[i - 1][j - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i + 1][j] + tempGreen[i - 1][j] + tempGreen[i + 1][j - 1] + tempGreen[i][j - 1] + tempGreen[i - 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i + 1][j] + tempBlue[i - 1][j] + tempBlue[i + 1][j - 1] + tempBlue[i][j - 1] + tempBlue[i - 1][j - 1];
                
                int averageRed = round(sumRed / 6);
                int averageGreen = round(sumGreen / 6);
                int averageBlue = round(sumBlue / 6);
                
                image[i][j].rgbtRed = averageRed;
                image[i][j].rgbtGreen = averageGreen;
                image[i][j].rgbtBlue = averageBlue;
            }
            
            //for middle parts
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                float averageRed = 0;
                float averageGreen = 0;
                float averageBlue = 0;
                
                for (int k = i - 1; k <= i + 1; k++)
                {
                    for (int l = j - 1; l <= j + 1; l++)
                    {
                        averageRed += tempRed[k][l];
                        averageGreen += tempGreen[k][l];
                        averageBlue += tempBlue[k][l];
                    }
                }
                
                image[i][j].rgbtRed = round(averageRed / 9);
                image[i][j].rgbtGreen = round(averageGreen / 9);
                image[i][j].rgbtBlue = round(averageBlue / 9);
            }
        }
    }
    return;
}
