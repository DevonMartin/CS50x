#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average value of the R, G, and B values
            float k = image[i][j].rgbtBlue;
            float l = image[i][j].rgbtGreen;
            float m = image[i][j].rgbtRed;
            int n = round((k + l + m) / 3);

            // Set each value to the average of the three, to turn the pixel grayscale
            image[i][j].rgbtBlue = n;
            image[i][j].rgbtGreen = n;
            image[i][j].rgbtRed = n;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* Create a temporary RGBTRIPLE to store pixels in, as
       the image being edited in real-time would alter the
       calculations to determin new pixels */
    RGBTRIPLE tmp[height][width];

    // Iterate through every pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Save each pixel's RGB values in the horizontally opposite
               temp variable's pixel */
            int k = image[i][j].rgbtBlue;
            int l = image[i][j].rgbtGreen;
            int m = image[i][j].rgbtRed;
            tmp[i][width - j - 1].rgbtBlue = k;
            tmp[i][width - j - 1].rgbtGreen = l;
            tmp[i][width - j - 1].rgbtRed = m;
        }

        // Save each temp (now completed) pixel back into the original image
        for (int j = 0; j < width; j++)
        {
            int k = tmp[i][j].rgbtBlue;
            int l = tmp[i][j].rgbtGreen;
            int m = tmp[i][j].rgbtRed;
            image[i][j].rgbtBlue = k;
            image[i][j].rgbtGreen = l;
            image[i][j].rgbtRed = m;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* Create a temporary RGBTRIPLE to store pixels in, as
       the image being edited in real-time would alter the
       calculations to determin new pixels */
    RGBTRIPLE tmp[height][width];

    // Iterate through every pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            /* Set variables for the sum of each RGB value for all surrounding
               pixels of the target, plus a counter to determine how many
               pixels are surrounding it */
            float sum_blue = 0, sum_green = 0, sum_red = 0, counter = 0;

            // Iterate through each surrounding pixel of the target
            for (int i = h - 1; i <= h + 1; i++)
            {
                for (int j = w - 1; j <= w + 1; j++)
                {

                    /* Ensure each surrounding pixel is within the bounds of
                       the original image */
                    if (i >= 0 && i < height && j >= 0 && j < width)
                    {

                        /* For each acceptable pixel, add its RGB values to the
                           sums and add 1 to the counter */
                        sum_blue += image[i][j].rgbtBlue;
                        sum_green += image[i][j].rgbtGreen;
                        sum_red += image[i][j].rgbtRed;
                        counter++;
                    }
                }
            }

            // Calculate new target RGB value as the average of surrounding pixels
            tmp[h][w].rgbtBlue = round(sum_blue / counter);
            tmp[h][w].rgbtGreen = round(sum_green / counter);
            tmp[h][w].rgbtRed = round(sum_red / counter);
        }
    }

    // Cycle through each pixel and replace image with temp image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int k = tmp[h][w].rgbtBlue;
            int l = tmp[h][w].rgbtGreen;
            int m = tmp[h][w].rgbtRed;
            image[h][w].rgbtBlue = k;
            image[h][w].rgbtGreen = l;
            image[h][w].rgbtRed = m;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE tmp[height][width];

    // Iterate through every pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            // Set my pixel calculations back to 0 for each pixel iteration
            float sum_blue_x = 0, sum_green_x = 0, sum_red_x = 0, sum_blue_y = 0, sum_green_y = 0, sum_red_y = 0;

            // Cycle through each surrounding pixel
            for (int hm = h - 1; hm <= h + 1; hm++)
            {
                for (int wm = w - 1; wm <= w + 1; wm++)
                {

                    // Check for out-of-bounds pixels
                    if (hm >= 0 && hm < height && wm >= 0 && wm < width)
                    {

                        // Run through all Gx calculations
                        // Top left + bottom left
                        if ((hm == h - 1 && wm == w - 1) || (hm == h + 1 && wm == w - 1))
                        {
                            sum_blue_x -= image[hm][wm].rgbtBlue;
                            sum_green_x -= image[hm][wm].rgbtGreen;
                            sum_red_x -= image[hm][wm].rgbtRed;
                        }

                        // Top right + bottom right
                        else if ((hm == h - 1 && wm == w + 1) || (hm == h + 1 && wm == w + 1))
                        {
                            sum_blue_x += image[hm][wm].rgbtBlue;
                            sum_green_x += image[hm][wm].rgbtGreen;
                            sum_red_x += image[hm][wm].rgbtRed;
                        }

                        // Middle left
                        else if (hm == h && wm == w - 1)
                        {
                            sum_blue_x -= (image[hm][wm].rgbtBlue * 2);
                            sum_green_x -= (image[hm][wm].rgbtGreen * 2);
                            sum_red_x -= (image[hm][wm].rgbtRed * 2);
                        }

                        // Middle right
                        else if (hm == h && wm == w + 1)
                        {
                            sum_blue_x += (image[hm][wm].rgbtBlue * 2);
                            sum_green_x += (image[hm][wm].rgbtGreen * 2);
                            sum_red_x += (image[hm][wm].rgbtRed * 2);
                        }

                        // Run through all Yx calculations
                        // Top left + top right
                        if ((hm == h - 1 && wm == w - 1) || (hm == h - 1 && wm == w + 1))
                        {
                            sum_blue_y -= image[hm][wm].rgbtBlue;
                            sum_green_y -= image[hm][wm].rgbtGreen;
                            sum_red_y -= image[hm][wm].rgbtRed;
                        }

                        // Bottom left + bottom right
                        else if ((hm == h + 1 && wm == w - 1) || (hm == h + 1 && wm == w + 1))
                        {
                            sum_blue_y += image[hm][wm].rgbtBlue;
                            sum_green_y += image[hm][wm].rgbtGreen;
                            sum_red_y += image[hm][wm].rgbtRed;
                        }

                        // Top middle
                        else if (hm == h - 1 && wm == w)
                        {
                            sum_blue_y -= (image[hm][wm].rgbtBlue * 2);
                            sum_green_y -= (image[hm][wm].rgbtGreen * 2);
                            sum_red_y -= (image[hm][wm].rgbtRed * 2);
                        }

                        // Bottom middle
                        else if (hm == h + 1 && wm == w)
                        {
                            sum_blue_y += (image[hm][wm].rgbtBlue * 2);
                            sum_green_y += (image[hm][wm].rgbtGreen * 2);
                            sum_red_y += (image[hm][wm].rgbtRed * 2);
                        }
                    }
                }
            }

            /* Calculate new RGB values, ensure they're within boundary,
               and assign the new value to the temp image */
            int k = round(sqrt(pow(sum_blue_x, 2) + pow(sum_blue_y, 2)));
            if (k > 255)
                k = 255;
            tmp[h][w].rgbtBlue = k;

            int l = round(sqrt(pow(sum_green_x, 2) + pow(sum_green_y, 2)));
            if (l > 255)
                l = 255;
            tmp[h][w].rgbtGreen = l;

            int m = round(sqrt(pow(sum_red_x, 2) + pow(sum_red_y, 2)));
            if (m > 255)
                m = 255;
            tmp[h][w].rgbtRed = m;
        }
    }

    // Cycle through each pixel and replace image with temp image
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int k = tmp[h][w].rgbtBlue;
            int l = tmp[h][w].rgbtGreen;
            int m = tmp[h][w].rgbtRed;
            image[h][w].rgbtBlue = k;
            image[h][w].rgbtGreen = l;
            image[h][w].rgbtRed = m;
        }
    }
    return;
}

