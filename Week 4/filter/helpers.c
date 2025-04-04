#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Take average of red, green, and blue
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;

            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Compute sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            // Update pixel with sepia values
            if (sepiaBlue > 255) {
                image[i][j].rgbtBlue = 255;
            } else {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            if (sepiaGreen > 255) {
                image[i][j].rgbtGreen = 255;
            } else {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaRed > 255) {
                image[i][j].rgbtRed = 255;
            } else {
                image[i][j].rgbtRed = sepiaRed;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di, nj = j + dj;

                    if (ni >= 0 && ni < height && nj >=0 && nj < width) {
                        sumRed += copy[ni][nj].rgbtRed;
                        sumGreen += copy[ni][nj].rgbtGreen;
                        sumBlue += copy[ni][nj].rgbtBlue;

                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float)sumRed / count);
            image[i][j].rgbtGreen = round((float)sumGreen / count);
            image[i][j].rgbtBlue = round((float)sumBlue / count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }

    int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int Gx = 0, Gy = 0, final;

            // For red
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = di + i, nj = dj + j;

                    if (ni >= 0 && ni < height && nj >=0 && nj < width) {
                        Gx += copy[i + di][j + dj].rgbtRed * GxKernel[di + 1][dj + 1];
                        Gy += copy[i + di][j + dj].rgbtRed * GyKernel[di + 1][dj + 1];
                    }
                }
            }

            final = round(sqrt(Gx * Gx + Gy * Gy));

            if (final > 255) {
                image[i][j].rgbtRed = 255;
            } else {
                image[i][j].rgbtRed = final;
            }

            Gx = 0;
            Gy = 0;

            // For green
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = di + i, nj = dj + j;

                    if (ni >= 0 && ni < height && nj >=0 && nj < width) {
                        Gx += copy[i + di][j + dj].rgbtGreen * GxKernel[di + 1][dj + 1];
                        Gy += copy[i + di][j + dj].rgbtGreen * GyKernel[di + 1][dj + 1];
                    }
                }
            }

            final = round(sqrt(Gx * Gx + Gy * Gy));

            if (final > 255) {
                image[i][j].rgbtGreen = 255;
            } else {
                image[i][j].rgbtGreen = final;
            }

            Gx = 0;
            Gy = 0;

            // For blue
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = di + i, nj = dj + j;

                    if (ni >= 0 && ni < height && nj >=0 && nj < width) {
                        Gx += copy[i + di][j + dj].rgbtBlue * GxKernel[di + 1][dj + 1];
                        Gy += copy[i + di][j + dj].rgbtBlue * GyKernel[di + 1][dj + 1];
                    }
                }
            }

            final = round(sqrt(Gx * Gx + Gy * Gy));

            if (final > 255) {
                image[i][j].rgbtBlue = 255;
            } else {
                image[i][j].rgbtBlue = final;
            }
        }
    }

    return;
}
