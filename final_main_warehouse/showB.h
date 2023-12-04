#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showBasket() //show the basket
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
        printf("|");
        int col = 0; sum = 0;
        token = strtok(line, "-");
        while (token)
        {
            if (col == 0)
                printf(" ");
            if (col == 1 || col == 3 )
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
                printf("  %.2lf\n", sum);
            }
            col++;
            if (col == 4)
                token = strtok(NULL, "\n");
            else 
            {
                token = strtok(NULL, "-");
            }
        }
        printf("\n");
    }
    if (count == 0)
    {
        printf("|\tYour basket is empty\n");
    }
    printf("---------------------------------\n");
    fclose(basketFile);
}