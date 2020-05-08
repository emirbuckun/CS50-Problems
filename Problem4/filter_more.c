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
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i + 1][j] + tempRed[i + 1][j + 1] + tempRed[i][j - 1] + tempRed[i + 1][j
                               - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j + 1] + tempGreen[i][j - 1] +
                                 tempGreen[i + 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j + 1] + tempBlue[i][j - 1] + tempBlue[i
                                + 1][j - 1];

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
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i + 1][j] + tempRed[i + 1][j + 1] + tempRed[i - 1][j] + tempRed[i - 1][j
                               + 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i + 1][j] + tempGreen[i + 1][j + 1] + tempGreen[i - 1][j] +
                                 tempGreen[i - 1][j + 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i + 1][j] + tempBlue[i + 1][j + 1] + tempBlue[i - 1][j] + tempBlue[i
                                - 1][j + 1];

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
                float sumRed = tempRed[i][j] + tempRed[i][j + 1] + tempRed[i - 1][j] + tempRed[i - 1][j + 1] + tempRed[i][j - 1] + tempRed[i - 1][j
                               - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i][j + 1] + tempGreen[i - 1][j] + tempGreen[i - 1][j + 1] + tempGreen[i][j - 1] +
                                 tempGreen[i - 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i][j + 1] + tempBlue[i - 1][j] + tempBlue[i - 1][j + 1] + tempBlue[i][j - 1] + tempBlue[i
                                - 1][j - 1];

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
                float sumRed = tempRed[i][j] + tempRed[i + 1][j] + tempRed[i - 1][j] + tempRed[i + 1][j - 1] + tempRed[i][j - 1] + tempRed[i - 1][j
                               - 1];
                float sumGreen = tempGreen[i][j] + tempGreen[i + 1][j] + tempGreen[i - 1][j] + tempGreen[i + 1][j - 1] + tempGreen[i][j - 1] +
                                 tempGreen[i - 1][j - 1];
                float sumBlue = tempBlue[i][j] + tempBlue[i + 1][j] + tempBlue[i - 1][j] + tempBlue[i + 1][j - 1] + tempBlue[i][j - 1] + tempBlue[i
                                - 1][j - 1];

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed[height + 2][width + 2];
    int tempGreen[height + 2][width + 2];
    int tempBlue[height + 2][width + 2];

    //create black borders for first and last row
    for (int a = 0; a < width + 2; a++)
    {
        tempRed[0][a] = 0;
        tempGreen[0][a] = 0;
        tempBlue[0][a] = 0;
        tempRed[height + 1][a] = 0;
        tempGreen[height + 1][a] = 0;
        tempBlue[height + 1][a] = 0;
    }

    //create black borders for first and last column
    for (int b = 0; b < height + 2; b++)
    {
        tempRed[b][0] = 0;
        tempGreen[b][0] = 0;
        tempBlue[b][0] = 0;
        tempRed[b][width + 1] = 0;
        tempGreen[b][width + 1] = 0;
        tempBlue[b][width + 1] = 0;
    }

    //create temp colors
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            tempRed[c + 1][d + 1] = image[c][d].rgbtRed;
            tempGreen[c + 1][d + 1] = image[c][d].rgbtGreen;
            tempBlue[c + 1][d + 1] = image[c][d].rgbtBlue;
        }
    }

    //calculate gx and gy
    int GxRed = 0;
    int GxGreen = 0;
    int GxBlue = 0;
    
    int GyRed = 0;
    int GyGreen = 0;
    int GyBlue = 0;
    
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            //calculate gx for each color
            GxRed = tempRed[i - 1][j - 1]  * -1 + tempRed[i][j - 1] * -2 + tempRed[i + 1][j - 1] * -1 + tempRed[i - 1][j + 1] * 1 + tempRed[i][j 
                    + 1] * 2 + tempRed[i + 1][j + 1] * 1; 
            GxGreen = tempGreen[i - 1][j - 1]  * -1 + tempGreen[i][j - 1] * -2 + tempGreen[i + 1][j - 1] * -1 + tempGreen[i - 1][j + 1] * 1 +
                      tempGreen[i][j + 1] * 2 + tempGreen[i + 1][j + 1] * 1; 
            GxBlue = tempBlue[i - 1][j - 1] * -1 + tempBlue[i][j - 1] * -2 + tempBlue[i + 1][j - 1] * -1 + tempBlue[i - 1][j + 1] * 1 +
                     tempBlue[i][j + 1] * 2 + tempBlue[i + 1][j + 1] * 1; 
            
            //calculate gy for each color
            GyRed = tempRed[i - 1][j - 1]  * -1 + tempRed[i - 1][j] * -2 + tempRed[i - 1][j + 1] * -1 + tempRed[i + 1][j - 1] * 1 + tempRed[i +
                    1][j] * 2 + tempRed[i + 1][j + 1] * 1; 
            GyGreen = tempGreen[i - 1][j - 1]  * -1 + tempGreen[i - 1][j] * -2 + tempGreen[i - 1][j + 1] * -1 + tempGreen[i + 1][j - 1] * 1 +
                      tempGreen[i + 1][j] * 2 + tempGreen[i + 1][j + 1] * 1; 
            GyBlue = tempBlue[i - 1][j - 1] * -1 + tempBlue[i - 1][j] * -2 + tempBlue[i - 1][j + 1] * -1 + tempBlue[i + 1][j - 1] * 1 +
                     tempBlue[i + 1][j] * 2 + tempBlue[i + 1][j + 1] * 1; 
            
            //combine gx and gy
            int red = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int green = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int blue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            
            if (red > 255)
            {
                image[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtRed = red;
            }
            
            if (green > 255)
            {
                image[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtGreen = green;
            }
            
            if (blue > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtBlue = blue;
            }
        }
    }

    return;
}
