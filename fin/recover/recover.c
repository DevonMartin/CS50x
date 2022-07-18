#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // Ensure the program is being used to open one single file
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Define an 8 bit unsigned integer as a BYTE for ease of use
    typedef uint8_t BYTE;
    int BLOCK_SIZE = sizeof(BYTE) * 512;
    int jpg_count = 0;

    // Open the file for reading purposes
    FILE *input = fopen(argv[1], "r");

    // Check that the file was opened successfully
    if (input == NULL)
    {
        printf("The file could not be opened.\n");
        return 1;
    }

    // Create buffer space to hold the info read from file below
    BYTE *buffer = (malloc(BLOCK_SIZE + 1));

    // Create an unsigned string the size of the photo's names (000.jpg)
    char *file_name = malloc(sizeof(char) * 8);
    if (file_name == NULL)
    {
        printf("Failed to allocate memory to file_name");
        return 2;
    }

    // Declare variable for saving photos
    FILE *jpg_file;

    /* Until we have finished looping through the file,
        continue looping through the file 512 BYTES at a time.
        Store data looped through in buffer */
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // If the beginning of the new info obtained is the start of a new photo
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xFF && (buffer[3] & 0xf0) == 0xe0)
        {
            // If this is not the first photo, close previous photo file
            if (jpg_count > 0)
            {
                fclose(jpg_file);
            }
            // Update file name, open new file, update file count, write buffer into jpg
            sprintf(file_name, "%03i.jpg", jpg_count);
            jpg_file = fopen(file_name, "w");
            jpg_count++;
        }
        // If JPGs are writing, continue writing
        if (jpg_count > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, jpg_file);
        }
    }

    // Return all memory
    fclose(jpg_file);
    fclose(input);
    free(file_name);
    free(buffer);
}