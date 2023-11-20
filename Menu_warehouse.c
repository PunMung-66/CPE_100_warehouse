#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    float quantity, initial, sell;
} product;

int menuwarehouse() {
    FILE *inputFile = fopen("database.csv", "r");
    if (inputFile == NULL) {
        printf("Error opening the input CSV file\n");
        return 1;
    }

    product selling[MAX_RECORDS];
    int numRecords = 0;
    char line[MAX_FIELD_SIZE];

    // Skip the first line (header)
    fgets(line, sizeof(line), inputFile);

    while (fgets(line, sizeof(line), inputFile) && numRecords < MAX_RECORDS) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(selling[numRecords].code, token);
            token = strtok(NULL, ",");
            selling[numRecords].quantity = atof(token);
            token = strtok(NULL, ",");
            strcpy(selling[numRecords].name, token);
            token = strtok(NULL, ",");
            selling[numRecords].initial = atof(token);
            token = strtok(NULL, ",");
            selling[numRecords].sell = atof(token);
            numRecords++;
        }
    }

    fclose(inputFile);
    printf("Select your option\n(1) Update stock\n(2) Show stock\n(3) Net profit\n(4) Exit\n");

    // Print alert
    for (int i = 0; i < numRecords; i++) {
        if (selling[i].quantity <= 4) {
            printf("%s has only %.0f left!!\n", selling[i].name, selling[i].quantity);
        }
    }

    // Choose option
     int a, inputResult;

    while (1) {
        printf("Please input your option: ");
        inputResult = scanf(" %d", &a);
        if (inputResult == 1 && (a == 1 || a == 2 || a == 3 || a == 4)) {
            break; // Valid input, exit the loop
        } else {
            printf("Please input a valid number (1, 2, 3, or 4)\n");  // Clear the input buffer
            while (getchar() != '\n');   // Keep reading characters until a newline is encountered
        }
    }
    printf("Selected option: %d\n", a);

    // Perform action based on the selected option
    if (a == 1) {
        printf("Update stock\n");
    } else if (a == 2) {
        // Show stock
        printf("            ==Welcome to Warehouse menu==\n");
        printf("Code               Quantity         name               initial         sell\n");
        for (int i = 0; i < numRecords; i++) {
            printf("%-20s%-15.2f%-20s%-15.2f%-15.2f\n", selling[i].code, selling[i].quantity, selling[i].name, selling[i].initial, selling[i].sell);
        }
    } else if (a == 3) {
        printf("Net profit\n");
    } else if (a == 4) {
        printf("Exit\n");
    }

    return 0;
}

int main()
{
    menuwarehouse();
    return 0;
}