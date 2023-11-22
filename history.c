#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 100
#define CODE_WIDTH 5
#define UNIT_WIDTH 5
#define NAME_WIDTH 15
#define INITIAL_WIDTH 10
#define SELL_WIDTH 10

int ShowStocks();
void AddUnit();
void AddNewProduct();
void EditProduct();
void add_in_his(char *code, int unit, char *name, double initial, double sell);

int UpdateStock() {
    int choice;

    do {
        printf("1. Add Units\n");
        printf("2. Add New Product\n");
        printf("3. Edit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {

            case 1:
                ShowStocks();
                AddUnit();
                break;
            case 2:
                ShowStocks();
                AddNewProduct();
                break;
            case 3:
                ShowStocks();
                EditProduct();
                break;
            case 4:
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

        printf("%-*s%-*s%-*s%-*s%-*s\n", CODE_WIDTH, "Code", UNIT_WIDTH, "Unit", NAME_WIDTH, "Name", INITIAL_WIDTH, "Initial", SELL_WIDTH, "Sell");

        char code[CODE_WIDTH];
        int unit;
        char name[NAME_WIDTH];
        float initial, sell;

        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
            printf("%-*s%-*d%-*s%-*.2f%-*.2f\n", CODE_WIDTH, code, UNIT_WIDTH, unit, NAME_WIDTH, name, INITIAL_WIDTH, initial, SELL_WIDTH, sell);
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
    float initial, sell;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        if (strcmp(code, targetCode) == 0) {
            unit += additionalUnits;
        }
        fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
    }

    add_in_his(code,unit,name,initial,sell);
    fclose(file);
    fclose(tempFile);
    remove("Database.csv");
    rename("temp.csv", "Database.csv");

    printf("Units added successfully.\n");
}
void AddNewProduct() {
    char newCode[CODE_WIDTH];
    int newUnit;
    char newName[NAME_WIDTH];
    float newInitial, newSell;

    printf("Enter the new product code: ");
    scanf("%s", newCode);

    printf("Enter the number of units: ");
    scanf("%d", &newUnit);

    printf("Enter the product name: ");
    scanf("%s", newName);

    printf("Enter the initial price: ");
    scanf("%f", &newInitial);

    printf("Enter the sell price: ");
    scanf("%f", &newSell);

    FILE *file = fopen("Database.csv", "a");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return;
    }


    fprintf(file, "%s,%d,%s,%.2f,%.2f\n", newCode, newUnit, newName, newInitial, newSell);
    add_in_his(newCode, newUnit, newName, newInitial, newSell);
    fclose(file);

    printf("New product added successfully.\n");
}
void EditProduct() {
    char targetCode[CODE_WIDTH];
    char newName[NAME_WIDTH];
    int newUnit;
    float newInitial, newSell;

    printf("Enter the product code to edit: ");
    scanf("%s", targetCode);

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
    float initial, sell;

    int found = 0;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        if (strcmp(code, targetCode) == 0) {
            printf("Current details for product %s:\n", targetCode);
            printf("Name: %s\n", name);
            printf("Enter new product name: ");
            scanf("%s", newName);

            printf("Enter new number of units: ");
            scanf("%d", &newUnit);

            printf("Enter new initial price: ");
            scanf("%f", &newInitial);

            printf("Enter new sell price: ");
            scanf("%f", &newSell);

            strcpy(name, newName);
            unit = newUnit;
            initial = newInitial;
            sell = newSell;

            found = 1;
        }
        fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
    }

    fclose(file);
    fclose(tempFile);

    remove("Database.csv");
    rename("temp.csv", "Database.csv");

    if (found) {
        printf("Product %s edited successfully.\n", targetCode);
    } else {
        printf("Product %s not found.\n", targetCode);
    }
}

void add_in_his(char *code, int unit, char *name, double initial, double sell)
{
    FILE *fp;
    fp=fopen("history.csv","a");
    if(fp==NULL)
    {
        printf("Error in opening file");
        exit(1);
    }
    fprintf(fp,"%s,%d,%s,%.2f,%.2f",code,unit,name,initial,sell);
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(fp,",%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    fprintf(fp,",%d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    fclose(fp);
}

int main(){
  UpdateStock();
}