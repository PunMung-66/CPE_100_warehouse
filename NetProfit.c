#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    double quantity, cost, sell;
} ProductBasket;

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

int netprofit(){
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

int main(){
    netprofit();

    return 0;
}

