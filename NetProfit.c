/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    double quantity, cost, sell;
} ProductBasket;

double total[2] = {200,500};

void printReceipt(ProductBasket *receipt, int numRecords) {
    printf("%-11s%-15s%-10s%-10s%-10s\n", "Code", "Quantity", "Name", "Cost", "Sell");
    printf("=========================================================\n");
    for (int i = 0; i < numRecords; i++) {
        printf("%-12s%-13.2lf%-11s%-10.2lf%-10.2lf\n",
               receipt[i].code,
               receipt[i].quantity,
               receipt[i].name,
               receipt[i].cost,
               receipt[i].sell);
    }
}

int showstruct(){
    FILE *file = fopen("baskettemp.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    ProductBasket receipt[MAX_RECORDS];
    int numRecords = 0;

    // Read data from the file into the array of structs
    while (fscanf(file, "%[^-]-%[^-]-%lf-%lf-%lf",
                  receipt[numRecords].code,
                  receipt[numRecords].name,
                  &receipt[numRecords].quantity,
                  &receipt[numRecords].cost,
                  &receipt[numRecords].sell) == 5) {
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }
    fclose(file);
    printReceipt(receipt, numRecords);
    return 0;
}

void sellorder(){
    FILE *file = fopen("baskettemp.txt", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    ProductBasket receipt[MAX_RECORDS];
    int numRecords = 0;

    // Read data from the file into the array of structs
    while (fscanf(file, "%[^-]-%[^-]-%lf-%lf-%lf",
                  receipt[numRecords].code,
                  receipt[numRecords].name,
                  &receipt[numRecords].quantity,
                  &receipt[numRecords].cost,
                  &receipt[numRecords].sell) == 5) {
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }
    fclose(file);
    
    return 0;
}
int main(){
    showstruct();

    return 0;
}*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    double quantity, cost, sell;
} ProductBasket;

double total[2] = {2000, 5000};
//total[0] -> 2000 = total cost | total[1] -> 5000 = total profit

void printReceipt(ProductBasket *receipt, int numRecords) {
    printf("%-11s%-15s%-10s%-10s%-10s\n", "Code", "Quantity", "Name", "Cost", "Sell");
    printf("=========================================================\n");
    for (int i = 0; i < numRecords; i++) {
        printf("%-12s%-13.2lf%-11s%-10.2lf%-10.2lf\n",
               receipt[i].code,
               receipt[i].quantity,
               receipt[i].name,
               receipt[i].cost,
               receipt[i].sell);
    }
}

void updateUnits(const char *targetCode, double amount) {
    FILE *file = fopen("baskettemp.txt", "r");
    FILE *tempFile = fopen("tempbasket.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    ProductBasket receipt[MAX_RECORDS];
    int numRecords = 0;

    while (fscanf(file, "%[^-]-%[^-]-%lf-%lf-%lf",
                  receipt[numRecords].code,
                  receipt[numRecords].name,
                  &receipt[numRecords].quantity,
                  &receipt[numRecords].cost,
                  &receipt[numRecords].sell) == 5) {
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }

    int found = 0;

    for (int i = 0; i < numRecords; i++) {
        if (strcmp(receipt[i].code, targetCode) == 0) {
            if (receipt[i].quantity >= amount) {
                receipt[i].quantity -= amount;
                found = 1;
            } else {
                printf("Not enough quantity available for product %s.\n", targetCode);
            }
            break;
        }
    }

    if (!found) {
        printf("Product %s not found.\n", targetCode);
    }

    for (int i = 0; i < numRecords; i++) {
        fprintf(tempFile, "%s-%s-%.2lf-%.2lf-%.2lf\n",
                receipt[i].code,
                receipt[i].name,
                receipt[i].quantity,
                receipt[i].cost,
                receipt[i].sell);
    }

    fclose(file);
    fclose(tempFile);

    remove("baskettemp.txt");
    rename("tempbasket.txt", "baskettemp.txt");

    if (found) {
        printf("Units for product %s updated successfully.\n", targetCode);
    }
}

int main() {
    // Example usage of updateUnits function
    updateUnits("M001", 3);

    return 0;
}


