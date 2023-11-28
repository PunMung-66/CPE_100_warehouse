#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ShowStocks() {
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
        printf("%-*s%-*s%-*s%-*s%-*s\n", 10, "Code", 15, "Unit", 15, "Name", 15, "Cost", 15, "Sell");
        char code[100];
        int unit;
        char name[100];
        float cost, sell;
        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) {
            printf("%-*s%-*d%-*s%-*.2f%-*.2f\n", 10, code, 15, unit, 15, name, 15, cost, 15, sell);
        }
        fclose(file);

    }
    printf("\n");
    return 0;
}

int addToBasket(const char *code, char *name,int quantity) 
{
    FILE* basketFile = fopen("basket.txt", "a");
    if (basketFile == NULL) {
        printf("Error opening basket file.\n");
        return 0;
    }
    // Write the product code, name, and quantity to the basket file
    fprintf(basketFile, "%s - %s - %d\n", code, name, quantity);
    fclose(basketFile);
    return(1);
}

void showBasket() 
{
    char *token;
    FILE *basketFile = fopen("basket.txt", "r");
    FILE *file = fopen("Database.csv", "r");

    if (basketFile == NULL || file == NULL) {
        printf("Error opening basket file.\n");
    }
    printf("Your basket now:\n\n");
    printf("---------------------------------\n");
    char line[100];
    while (fgets(line, sizeof(line), basketFile) != NULL) 
    {
        token = strtok(line, "\n");
        printf("|\t%s\t|\n", token);
    }
    printf("---------------------------------\n");
    fclose(basketFile);
}

void addToBasket_system()
{
    char code_i[10];
    int quantity_i, add_finished = 0;
    //system("cls");
    ShowStocks();
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
                    add_finished = addToBasket(code, name, quantity_i);
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
            showBasket();
        }
        fclose(file);
    }
}



int main()
{
    addToBasket_system();
    return(0);
}