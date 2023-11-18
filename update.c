#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define CODE_WIDTH 5
#define UNIT_WIDTH 5
#define NAME_WIDTH 15
#define COST_WIDTH 10
#define SELL_WIDTH 10

int ShowStocks();
void AddUnit();

int UpdateStock() {
    int choice;

    do {
        printf("1. Add Unit\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {

            case 1:
                ShowStocks();
                AddUnit();
                break;
            case 2:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 3);

    return 0;
}

int ShowStocks() {
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    } else {
        char header[BUFFER_SIZE];
        int choice;
        fgets(header, sizeof(header), file);

        printf("%-*s%-*s%-*s%-*s%-*s\n", CODE_WIDTH, "Code", UNIT_WIDTH, "Unit", NAME_WIDTH, "Name", COST_WIDTH, "Cost", SELL_WIDTH, "Sell");

        char code[CODE_WIDTH];
        int unit;
        char name[NAME_WIDTH];
        float cost, sell;

        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) {
            printf("%-*s%-*d%-*s%-*.2f%-*.2f\n", CODE_WIDTH, code, UNIT_WIDTH, unit, NAME_WIDTH, name, COST_WIDTH, cost, SELL_WIDTH, sell);
        }

        fclose(file);

    }
    return 0;
}

void AddUnit() {
    char targetCode[CODE_WIDTH];
    int additionalUnits;

    printf("Enter product code to add units: ");
    scanf("%s", targetCode);

    printf("Enter the number of units to add: ");
    scanf("%d", &additionalUnits);

    FILE *file = fopen("Database.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char header[BUFFER_SIZE];
    fgets(header, sizeof(header), file);
    fprintf(tempFile, "%s", header);

    char code[CODE_WIDTH];
    int unit;
    char name[NAME_WIDTH];
    float cost, sell;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) {
        if (strcmp(code, targetCode) == 0) {
            unit += additionalUnits;
        }
        fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, cost, sell);
    }

    fclose(file);
    fclose(tempFile);

    remove("Database.csv");
    rename("temp.csv", "Database.csv");

    printf("Units added successfully.\n");
}

int main(){
  UpdateStock();
}