#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int BLOCKSIZE = 512;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./recover file\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t buffer[BLOCKSIZE];
    int fileCount = 1;

    FILE *img = NULL;
    char name[8];

    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, input) == BLOCKSIZE) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) {
            // Found a JPEG

            if (img != NULL) {
                fclose(img);
            }

            sprintf(name, "%03i.jpg", fileCount++);

            img = fopen(name, "w");

            fwrite(buffer, sizeof(buffer), 1, img);
        } else {
            if (img) { // If already found a JPEG
                fwrite(buffer, sizeof(buffer), 1, img);
            }
        }
    };

    if (img != NULL) {
        fclose(img);
    }

    fclose(input);
    return 0;
}
