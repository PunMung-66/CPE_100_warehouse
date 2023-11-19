#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "showB.h"


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
    int unit_b, add_finished = 0;;
    char name_b[15];
    float cost_b, sell_b;
    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code_b, &unit_b, name_b, &cost_b, &sell_b) == 5) 
    {
        if (strcmp(code_b, code[ch_line]) == 0)
        {
            if (unit_b < new_unit || unit_b == 0)
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
                printf(" x ");
            if (col != 3)
                printf("%s", token);
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