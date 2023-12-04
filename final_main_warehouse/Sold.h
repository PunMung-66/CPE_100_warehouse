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
    char line[99];
    while (fgets(line, sizeof(line), file) != NULL) 
    {
      int col = 0;
      char *token = strtok(line, "-");
      while (token)
      {
        if (col == 0)
          strcpy(receipt[numRecords].code, token);
        else if (col == 1)
          strcpy(receipt[numRecords].name, token);
        else if (col == 2)
          receipt[numRecords].quantity = atoi(token);
        else if (col == 3)
          receipt[col].cost = atof(token);
        else if (col == 4)
          receipt[numRecords].sell = atof(token);
        token = strtok(NULL, "-");
        col++;
      }
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }
    fclose(file);
    return numRecords;
}

int readProductData(Product *products) { //readproduct function
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) {
        printf("Error opening the file 'Database.csv'.\n");
        return 0;
    }
    int numRecords = 0;
    char header[MAX_FIELD_SIZE];
    char line[99];
    fgets(header, sizeof(header), file);
    while (fgets(line, sizeof(line), file) != NULL) 
    {
      int col = 0;
      char *token = strtok(line, ",");
      while (token)
      {
        if (col == 0)
          strcpy(products[numRecords].code, token);
        else if (col == 2)
          strcpy(products[numRecords].name, token);
        else if (col == 1)
          products[numRecords].unit = atoi(token);
        else if (col == 3)
          products[numRecords].initial = atof(token);
        else if (col == 4)
          products[numRecords].sell = atof(token);
        token = strtok(NULL, ",");
        col++;
      }
        numRecords++;
        if (numRecords >= MAX_RECORDS) {
            printf("Exceeded maximum number of records. Increase MAX_RECORDS if needed.\n");
            break;
        }
    }
    fclose(file);
    return numRecords;
}

void updateProductUnits(Product *products, int numProductRecords, ProductBasket *receipt, int numBasketRecords) { //update product
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
        printf("Error opening the file 'temp.csv' for writing.\n");
        return;
    }

    fprintf(file, "Code,Unit,Name,Initial(฿),Sell(฿)\n");

    for (int i = 0; i < numProductRecords; i++) {
        fprintf(file, "%s,%d,%s,%.2lf,%.2lf\n",
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