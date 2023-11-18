#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ShowStocks_cashier() {
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return 1;
    } 
    else 
    {
        char header[100];
        int choice;
        fgets(header, sizeof(header), file);
        printf("%-*s%-*s%-*s%-*s\n", 10, "Code", 15, "Unit", 15, "Name", 15, "Sell");
        char code[100];
        int unit;
        char name[100];
        float cost, sell;
        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) {
            printf("%-*s%-*d%-*s%-*.2f\n", 10, code, 15, unit, 15, name, 15, sell);
        }
        fclose(file);

    }
    printf("\n");
    return 0;
}

int addToBasket(const char* code, int quantity) 
{
    FILE* basketFile = fopen("basket.txt", "a");
    if (basketFile == NULL) {
        printf("Error opening basket file.\n");
        return 0;
    }

    // Write the product code, name, and quantity to the basket file
    fprintf(basketFile, "%s - %d\n", code, quantity);

    fclose(basketFile);
    return(1);
}

void showBasket() 
{
    FILE* basketFile = fopen("basket.txt", "r");
    if (basketFile == NULL) {
        printf("Error opening basket file.\n");
        return;
    }
    printf("Your basket now:\n");
    char line[100];
    while (fgets(line, sizeof(line), basketFile) != NULL) {
        printf("%s", line);
    }

    fclose(basketFile);
}

void addToBasket_system()
{
    char code_i[10];
    int quantity_i, add_finished = 0;
    //system("cls");
    ShowStocks_cashier();
    printf("Enter product (Code) to add in basket: ");
    scanf("%s", &code_i);
    printf("Enter the number of units to add: ");
    scanf("%d", &quantity_i);
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
    } 
    else
    {
        char header[100];
        fgets(header, sizeof(header), file);
        char code[10];
        int unit;
        char name[15];
        float cost, sell;
        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) 
        {
            if (strcmp(code, code_i) == 0)
                add_finished = addToBasket(code, quantity_i);
        }
        if (add_finished == 0)
        {
             system("cls");
            printf("\n(* Your product not found !!!! *)\n");
        }
        else
        {
            system("cls");
            printf("\n(* Your product has been added. *)\n");
            showBasket();
        }
        fclose(file);
    }
}
