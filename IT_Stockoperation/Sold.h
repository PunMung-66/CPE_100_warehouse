#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100
#define TOTAL_SIZE 2

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    double quantity, cost, sell;
} ProductBasket;

typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    int unit;
    double initial, sell;
} Product;
int readBasketData(ProductBasket *receipt) {
    FILE *file = fopen("basket.txt", "r");

    if (file == NULL) {
        printf("Error opening the file 'baskettmp.txt'.\n");
        return 0;
    }

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
    fclose(file);
    return numRecords;
}

int readProductData(Product *products) {
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) {
        printf("Error opening the file 'Database.csv'.\n");
        return 0;
    }
    int numRecords = 0;
    char header[MAX_FIELD_SIZE];
    fgets(header, sizeof(header), file);
    while (fscanf(file, "%[^,],%d,%[^,],%lf,%lf",
                  products[numRecords].code,
                  &products[numRecords].unit,
                  products[numRecords].name,
                  &products[numRecords].initial,
                  &products[numRecords].sell) == 5) {
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }
    fclose(file);
    return numRecords;
}

void updateProductUnits(Product *products, int numProductRecords, ProductBasket *receipt, int numBasketRecords) {
    for (int i = 0; i < numBasketRecords; i++) {
        for (int j = 0; j < numProductRecords; j++) {
            if (strcmp(receipt[i].code, products[j].code) == 0) {
                products[j].unit -= receipt[i].quantity;
                break; 
            }
        }
    }
}

void writeProductDataToFile(Product *products, int numProductRecords) {
    FILE *file = fopen("temp.csv", "w");

    if (file == NULL) {
        printf("Error opening the file 'Data.csv' for writing.\n");
        return;
    }
    fprintf(file, "Code,Unit,Name,Initial(฿),Sell(฿)\n");
    for (int i = 0; i < numProductRecords; i++) {
        fprintf(file, "%s,%d,%s,%.2lf,%.2lf",
                products[i].code,
                products[i].unit,
                products[i].name,
                products[i].initial,
                products[i].sell);
    }

    fclose(file);
    remove("Database.csv");
    rename("temp.csv", "Database.csv");
}
int Sold() {
    double total[TOTAL_SIZE] = {200, 500};
    ProductBasket receipt[MAX_RECORDS];
    Product products[MAX_RECORDS];
    int numBasketRecords = readBasketData(receipt);
    int numProductRecords = readProductData(products);
    updateProductUnits(products, numProductRecords, receipt, numBasketRecords);
    writeProductDataToFile(products, numProductRecords);
    printf("Stock Updated!!!");
    return 0;
}