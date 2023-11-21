#include <stdio.h>

struct Record {
    char code[10];
    char name[50];
    int amount;
    int sell;
    int profit;
};

void processStatement(const char *inputF, const char *outputF) {
    FILE *inputFile = fopen(inputF, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return;
    }

    FILE *outputFile = fopen(outputF, "w");
    if (outputFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(inputFile);
        return;
    }

    // Read and write headers
    fprintf(outputFile, "code, name, amount, sell, profit\n");

    struct Record record;
    while (fscanf(inputFile, "%9[^,],%49[^,],%d,%d,%d\n",
                  record.code, record.name, &record.amount, &record.sell, &record.profit) == 5) {

        // Write the modified record to the temporary file
        fprintf(outputFile, "%s, %s, %d, %.2lf, %.2lf\n",
                record.code, record.name, record.amount, record.sell, record.profit);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);
}
