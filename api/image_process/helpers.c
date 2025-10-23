#include "helpers.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            RGBTRIPLE current_pixel = image[h][w];
            RGBTRIPLE new_pixel;

            BYTE avg_color_value = (current_pixel.rgbtBlue + current_pixel.rgbtGreen + current_pixel.rgbtRed) / 3;
            new_pixel.rgbtBlue = avg_color_value;
            new_pixel.rgbtGreen = avg_color_value;
            new_pixel.rgbtRed = avg_color_value;
            image[h][w] = new_pixel;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            RGBTRIPLE current_pixel = image[h][w];
            RGBTRIPLE new_pixel;

            int sepiaRed = 0.393 * current_pixel.rgbtRed + 0.769 * current_pixel.rgbtGreen + 0.189 * current_pixel.rgbtBlue;
            int sepiaGreen = 0.349 * current_pixel.rgbtRed + 0.686 * current_pixel.rgbtGreen + 0.168 * current_pixel.rgbtBlue;
            int sepiaBlue = 0.272 * current_pixel.rgbtRed + 0.534 * current_pixel.rgbtGreen + 0.131 * current_pixel.rgbtBlue;

            //white pixels will be over 255, so we revert them to 255
            new_pixel.rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            new_pixel.rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            new_pixel.rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;


            image[h][w] = new_pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        int index = 0;
        for (int w = 0; w < width / 2; w++) {
            RGBTRIPLE left_pixel = image[h][width - index];
            RGBTRIPLE right_pixel = image[h][w];

            image[h][w] = left_pixel;
            image[h][width - index] = right_pixel;

            index += 1;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy so updates don't affect neighboring pixels mid-calculation
    RGBTRIPLE copy[height][width];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            copy[h][w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            RGBTRIPLE square[9];
            int current_index = 0;

            // loop through every surrounding square of the current pixel
            for (int square_height = -1; square_height <= 1; square_height++) {
                for (int square_width = -1; square_width <= 1; square_width++) {
                    int new_h = h + square_height;
                    int new_w = w + square_width;

                    // check bounds
                    if (new_h >= 0 && new_h < height && new_w >= 0 && new_w < width) {
                        square[current_index] = copy[new_h][new_w];
                        current_index++;
                    }
                }
            }

            DWORD avg_blue = 0, avg_green = 0, avg_red = 0;
            for (int i = 0; i < current_index; i++) {
                RGBTRIPLE current_pixel = square[i];
                avg_blue += current_pixel.rgbtBlue;
                avg_green += current_pixel.rgbtGreen;
                avg_red += current_pixel.rgbtRed;
            }

            avg_blue /= current_index;
            avg_green /= current_index;
            avg_red /= current_index;

            RGBTRIPLE new_pixel;
            new_pixel.rgbtBlue = avg_blue;
            new_pixel.rgbtGreen = avg_green;
            new_pixel.rgbtRed = avg_red;

            image[h][w] = new_pixel;
        }
    }
}

