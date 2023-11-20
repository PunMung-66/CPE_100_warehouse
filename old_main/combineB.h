#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char line[50],  name[100][30], code[100][30];
    int unit[100];
    double cost[100], sell[100], total_each[100] ,profit[100], total_cost = 0, total_profit = 0;
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
        total_profit += (sell[index] - cost[index]) * unit[index];
        total_cost += sell[index] * unit[index];
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
    for (int i = 0; i < index; i++)
    {
        if (unit[i] != 0)
            fprintf(Tempfile, "%s-%s-%d-%.2lf-%.2lf\n", code[i], name[i], unit[i], cost[i], sell[i]);
    }
    printf("total cost: %.2lf Baht\n", total_cost);
    printf("total profit: %.2lf Baht\n\n", total_profit);
    fclose(basketFile);
    fclose(Tempfile);
    remove("basket.txt");
    rename("temp.txt", "basket.txt");
}