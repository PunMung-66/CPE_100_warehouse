#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 100

int main() {
    FILE *file = fopen("data.csv", "a+"); // Open the file for appending and reading

    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Read the existing number from the file
    int existingNumber;
    if (fscanf(file, "%d", &existingNumber) != 1) {
        // Reading failed, set existingNumber to 0
        existingNumber = 0;
    }

    printf("Current number: %d\n", existingNumber);

    // Move the file pointer to the beginning to overwrite the existing content
    fseek(file, 0, SEEK_SET);
    // Update the file with the initial value of 0
    fprintf(file, "%d\n", existingNumber);

    // Close the file
    fclose(file);

    return 0;
}
