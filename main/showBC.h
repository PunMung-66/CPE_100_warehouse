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

void showBasket() 
{
    int count = 0;
    char *token, line[100];
    FILE *basketFile = fopen("basket.txt", "r");
    if (basketFile == NULL) {
        printf("Error opening basket file.\n");
    }
    printf("Your basket now:\n\n");
    printf("---------------------------------\n");
    while (fgets(line, sizeof(line), basketFile) != NULL) 
    {
        count++;
        token = strtok(line, "\n");
        printf("| %s \n", token);
    }
    if (count == 0)
    {
        printf("|\tYour basket is empty\n");
    }
    printf("---------------------------------\n");
    fclose(basketFile);
}