#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "showC.h"
#include "showB.h"

int unit_basket[100];
char name_basket[100][30], code_basket[100][30];

void combine_basket()
{
    FILE *basketFile = fopen("basket.txt", "r");
    FILE *Tempfile = fopen("temp.txt", "w");
    if (basketFile == NULL || Tempfile == NULL) {
        fclose(basketFile);
        fclose(Tempfile);
        remove("basket.txt");
        rename("temp.txt", "basket.txt");
        return;
        //printf("Error opening basket file.\n");
    }
    char line[50];
    double cost[100], sell[100], total_each[100] ,profit[100], total_cost = 0, total_profit = 0;
    int index = 0;
    while (fgets(line, sizeof(line), basketFile) != NULL)
    {
        char *token = strtok(line, "-");
        int col = 0;
        while (token != NULL)
        {
            if (col == 0)
                strcpy(code_basket[index], token);
            else if (col == 1)
                strcpy(name_basket[index], token);
            else if (col == 2)
                unit_basket[index] = atoi(token);
            else if (col == 3)
                cost[index] = atof(token);
            else if (col == 4)
                sell[index] = atof(token);
            token = strtok(NULL, "-");
            col++;
        }
        total_profit += (sell[index] - cost[index]) * unit_basket[index];
        total_cost += sell[index] * unit_basket[index];
        index++;
    }
    for (int i = 0; i < index; i++)
    {
        for (int j = i + 1; j < index; j++)
        {
            if (strcmp(code_basket[i], code_basket[j]) == 0)
            {
                unit_basket[i] += unit_basket[j];
                unit_basket[j] = 0;
            }
        }

    }
    for (int i = 0; i < index; i++)
    {
        if (unit_basket[i] != 0)
            fprintf(Tempfile, "%s-%s-%d-%.2lf-%.2lf\n", code_basket[i], name_basket[i], unit_basket[i], cost[i], sell[i]);
    }
    printf("total cost: %.2lf Baht\n", total_cost);
    printf("total profit: %.2lf Baht\n\n", total_profit);
    fclose(basketFile);
    fclose(Tempfile);
    remove("basket.txt");
    rename("temp.txt", "basket.txt");
}

int addToBasket(const char *code, char *name, int quantity, double cost, double sell) 
{
    FILE* basketFile = fopen("basket.txt", "a");
    if (basketFile == NULL) 
    {
        return 0;
        printf("Error opening basket file.\n");
    }
    fprintf(basketFile, "%s-%s-%d-%.2lf-%.2lf\n", code, name, quantity, cost, sell);
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
        printf("\n(* Your quantity is not valid !!!! *)\n\n");
    }
    else
    {
        char header[100];
        fgets(header, sizeof(header), file);
        char code[10];
        int unit, old_unit = 0;
        char name[15];
        float cost, sell;
        while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) 
        {
            if (strcmp(code, code_i) == 0)
            {
                int i = 0;
                while (strcmp(code_basket[i], code_i) != 0 && i < 100)
                    i++;
                if (i < 100)
                    old_unit = unit_basket[i];
                if (unit < (quantity_i + old_unit) || unit == 0)
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
            printf("\n(* Sorry our product is not enough !!!! *)\n\n");
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

void edit_basket(int ch_line)
{
    FILE *basketFile = fopen("basket.txt", "r");
    FILE *Tempfile = fopen("temp.txt", "w");
    FILE *file = fopen("Database.csv", "r");
    if (basketFile == NULL || Tempfile == NULL || file == NULL) {
        return;
        //printf("Error opening basket file.\n");
    }
    ch_line--;
    char line[50],  name[100][30], code[100][30];
    int unit[100];
    double cost[100], sell[100];
    int index = 0;
    while (fgets(line, sizeof(line), basketFile) != NULL)
    {
        char *token = strtok(line, "-");
        int col = 0;
        while (token != NULL)
        {
            if (col == 0)
                strcpy(code[index], token);
            else if (col == 1)
                strcpy(name[index], token);
            else if (col == 2)
                unit[index] = atoi(token);
            else if (col == 3)
                cost[index] = atof(token);
            else if (col == 4)
                sell[index] = atof(token);
            token = strtok(NULL, "-");
            col++;
        }
        index++;
    }
    for (int i = 0; i < index; i++)
    {
        for (int j = i + 1; j < index; j++)
        {
            if (strcmp(code[i], code[j]) == 0)
            {
                unit[i] += unit[j];
                unit[j] = 0;
            }
        }
    }
    printf("Enter the number of units to edit in %s %s:", code[ch_line], name[ch_line]);

    int new_unit;
    // unit[ch_line] = new_unit;
    scanf("%d", &new_unit);
    char header[100];
    fgets(header, sizeof(header), file);
    char code_b[10];
    int unit_b, old_unit = 0,add_finished = 0;
    char name_b[15];
    float cost_b, sell_b;
    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code_b, &unit_b, name_b, &cost_b, &sell_b) == 5) 
    {
        if (strcmp(code_b, code[ch_line]) == 0)
        {
            int i = 0;
            while (strcmp(code_basket[i], code_b) != 0 && i < 100)
                i++;
            if (i < 100)
                old_unit = unit_basket[i];
            if (unit_b < (new_unit + old_unit) || unit_b == 0)
            {
                    system("cls");
                    add_finished = - 1;
                    break;
            }
        }
    }
    fclose(file);

    if (add_finished == -1 || new_unit < 0)
    {
        system("cls");
        printf("\n(* Sorry our product is not enough !!!! *)\n\n");
        fclose(Tempfile);
        fclose(basketFile);
        remove("temp.txt");
        return;
    }
    if (add_finished == 0 )
    {
        unit[ch_line] = new_unit;
        for (int i = 0; i < index; i++)
        {
            if (unit[i] != 0)
                fprintf(Tempfile, "%s-%s-%d-%.2lf-%.2lf\n", code[i], name[i], unit[i], cost[i], sell[i]);
        }
        system("cls");
        printf("\n(* Your product has been edited. *)\n\n");
    }
    fclose(Tempfile);
    fclose(basketFile);
    remove("basket.txt");
    rename("temp.txt", "basket.txt");
}

int showBasket_edit()
{
    int count = 0, unit = 0;
    double sum = 0, sell = 0;
    char *token, line[100];
    FILE *basketFile = fopen("basket.txt", "r");
    if (basketFile == NULL) {
        //printf("Error opening basket file.\n");
    }
    printf("Your basket now:\n\n");
    printf("---------------------------------\n");
    while (fgets(line, sizeof(line), basketFile) != NULL) 
    {
        count++;
        printf("| (%d)", count);
        int col = 0;
        token = strtok(line, "-");
        while (token)
        {
            if (col == 0)
                printf(" ");
            if (col != 2 && col != 0)
                printf("\t");
            if (col == 2)
            {
                unit = atoi(token);
                printf(" x ");
            }
            if (col != 3)
                printf("%s", token);
            if ( col == 4)
            {
                sell = atof(token);
                sum += unit * sell;
                printf("  %.2lf", sum);
            }
            col++;
            token = strtok(NULL, "-");
        }
        printf("\n");
    }
    if (count == 0)
    {
        printf("|\tYour basket is empty\n");
    }
    printf("---------------------------------\n");
    fclose(basketFile);

    int option = 0;
    if (count != 0)
    {
        printf("\n\nEnter the (line) you need to edit (Enter 0 for cancel): ");
        scanf("%d", &option);
        if (option < 1 || option > count)
            option = 0;
    }
    return(option);
}

void editToBasket_system()
{
    int i = showBasket_edit();
    if (i == 0)
    {
        system("cls");
        printf("\n(* Your product not found in your basket !!!! *)\n\n");
    }
    else
    {
        edit_basket(i);
    }
}