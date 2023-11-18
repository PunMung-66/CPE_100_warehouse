#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void combine_same_product_in_basket()
{
    FILE *basketFile = fopen("basket.txt", "r");
    FILE *Tempfile = fopen("temp.txt", "w");
    if (basketFile == NULL || Tempfile == NULL) {
        return;
        //printf("Error opening basket file.\n");
    }
    char line[50],  name[100][30], code[100][30];
    int unit[100];
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
    for (int i = 0; i < index; i++)
    {
        if (unit[i] != 0)
            fprintf(Tempfile, "%s-%s- %d\n", code[i], name[i], unit[i]);
    }
    fclose(Tempfile);
    fclose(basketFile);
    remove("basket.txt");
    rename("temp.txt", "basket.txt");
}