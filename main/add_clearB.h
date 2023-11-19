#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "showBC.h"

int addToBasket(const char *code, char *name, int quantity, double cost, double sell) 
{
    FILE* basketFile = fopen("basket.txt", "a");
    if (basketFile == NULL) 
    {
        return 0;
        printf("Error opening basket file.\n");
    }
    fprintf(basketFile, "%s - %s - %d - %.2lf - %.2lf\n", code, name, quantity, cost, sell);
    fclose(basketFile);
    return(1);
}

void addToBasket_system()
{
    char code_i[10];
    int quantity_i, add_finished = 0;
    //system("cls");
    ShowStocks_cashier();
    printf("Enter product code to add in basket: ");
    scanf("%s", &code_i);
    printf("Enter the number of units to add: ");
    scanf("%d", &quantity_i);
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
    } 
    else if (quantity_i <= 0)
    {
        system("cls");
        printf("\n(* Your quantity is not valid !!!! *)\n");
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
            {
                if (unit < quantity_i || unit == 0)
                {
                    system("cls");
                    add_finished = - 1;
                    break;
                }
                else
                {
                    add_finished = addToBasket(code, name, quantity_i, cost, sell);
                    break;
                }
            }
        }
        system("cls");
        if (add_finished == 0)
            printf("\n(* Your product not found !!!! *)\n\n");
        else if (add_finished == -1)
            printf("\n(* Sorry our product is not enough !!!! *)\n");
        else
        {
            printf("\n(* Your product has been added. *)\n\n");
        }
        fclose(file);
    }
}

void clear_basket()
{
    FILE *file = fopen("basket.txt", "w");
    fclose(file);
    printf("\n(* Your basket has been cleared. *)\n\n");
}
