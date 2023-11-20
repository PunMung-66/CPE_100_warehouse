#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showBasket() 
{
    int count = 0;
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
}