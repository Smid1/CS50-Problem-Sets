#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t TWOBYTES;

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);
    fwrite (header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    float factor = atof(argv[3]);
    TWOBYTES sample;

    while (fread(&sample, sizeof(TWOBYTES), 2, input) != 0) {
        sample *= factor;
        fwrite(&sample, sizeof(TWOBYTES), 2, output);
    }

    fclose(input);
    fclose(output);
    return 0;
}
