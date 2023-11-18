#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char code[10];
    char name[MAX_NAME_LENGTH];
} Product;

void displayProducts(Product products[], int numProducts) {
    printf("Available Products:\n");
    for (int i = 0; i < numProducts; i++) {
        printf("%s - %s\n", products[i].code, products[i].name);
    }
}

void addToBasket(const char* code, int quantity) {
    FILE* basketFile = fopen("basket.txt", "a");
    if (basketFile == NULL) {
        printf("Error opening basket file.\n");
        return;
    }

    // Write the product code, name, and quantity to the basket file
    fprintf(basketFile, "%s - %d\n", code, quantity);

    fclose(basketFile);
}

int main() {
    // Read products from the "Database.csv" file
    FILE* databaseFile = fopen("Database.csv", "r");
    if (databaseFile == NULL) {
        printf("Error opening database file.\n");
        return 1;
    }

    Product products[MAX_PRODUCTS];
    int numProducts = 0;

    char line[100];
    while (fgets(line, sizeof(line), databaseFile) != NULL) {
        // Parse the line and extract the product code and name
        char* code = strtok(line, ",");
        char* name = strtok(NULL, ",");

        // Copy the code and name to the products array
        strcpy(products[numProducts].code, code);
        strcpy(products[numProducts].name, name);

        numProducts++;
    }

    fclose(databaseFile);

    // Display the products to the user
    displayProducts(products, numProducts);

    // Prompt the user to input the product code and quantity
    char code[10];
    int quantity;
    printf("Enter the product code: ");
    scanf("%s", code);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    // Search for the product with the given code
    int found = 0;
    for (int i = 0; i < numProducts; i++) {
        if (strcmp(products[i].code, code) == 0) {
            found = 1;
            addToBasket(products[i].name, quantity);
            break;
        }
    }

    if (found) {
        printf("Product added to basket.\n");
    } else {
        printf("Product not found.\n");
    }

    return 0;
}
