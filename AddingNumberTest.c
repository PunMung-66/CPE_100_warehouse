#include <stdio.h>

int main() {
    FILE *file = fopen("data.csv", "r+"); // Open the file for reading and updating

    if (file == NULL) {
        perror("Error opening the file");
        return 1;
    }

    // Read the existing number from the file
    int existingNumber;
    fscanf(file, "%d", &existingNumber);

    // Add a new number (e.g., 5) to the existing number
    int newNumber = existingNumber + 5;

    // Move the file pointer to the beginning to overwrite the existing number
    fseek(file, 0, SEEK_SET);
    // Update the file with the new combined number
    fprintf(file, "%d\n", newNumber);

    // Close the file
    fclose(file);

    printf("New number has been added to the file 'data.csv'\n");

    return 0;
}
