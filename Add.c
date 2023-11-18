#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 100
#define CODE_WIDTH 5
#define UNIT_WIDTH 5
#define NAME_WIDTH 15
#define COST_WIDTH 10
#define SELL_WIDTH 10

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
            fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, cost, sell);
        }
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