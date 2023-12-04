#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void  add_statement( int total_cost, int totl_profit)
{
    FILE *state_file = fopen("statement.csv", "a");
    FILE *basketFile = fopen("basket.txt", "r");
    if (basketFile == NULL) {
        
        printf("(* Your basket is empty *)");
        fclose(state_file);
        fclose(basketFile);
        return;
    }
    time_t timer;
    char time_n[26];
    struct tm* tm_info;

    timer = time(NULL);
    tm_info = localtime(&timer);

    strftime(time_n, 26, "%Y-%m-%d,%H:%M:%S", tm_info);
    printf("%s\n", time_n);

    int unit_basket, index = 0;
    char name_basket[100], code_basket[100];
    char line[50];
    double cost, sell;
    while (fgets(line, sizeof(line), basketFile) != NULL)
    {
        char *token = strtok(line, "-");
        int col = 0;
        while (token != NULL)
        {
            if (col == 0)
                strcpy(code_basket, token);
            else if (col == 1)
                strcpy(name_basket, token);
            else if (col == 2)
                unit_basket = atoi(token);
            else if (col == 3)
                cost = atof(token);
            else if (col == 4)
                sell = atof(token);
            token = strtok(NULL, "-");
            col++;
        }
        index++;
        fprintf(state_file,"%s,%s,%d,%s,%lf,%lf\n", time_n, code_basket, unit_basket, name_basket, cost, sell);
        //printf("%s,%d,%s,%lf,%lf,%s\n", code_basket, unit_basket, name_basket, cost, sell, time_n);
    }
    if (index != 0 && fgets(line, sizeof(line), basketFile) == NULL)
    {
        fprintf(state_file, "%s,%s,%d,%s,%s,%d\n", time_n, "Total", total_cost, "", "Profit", totl_profit);
        fprintf(state_file, ",,,,,,\n");
    }

    fclose(basketFile);
    fclose(state_file);
    return;
}