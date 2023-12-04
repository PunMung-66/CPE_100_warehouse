#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ShowStocks_cashier() { //showstock in cashier
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) 
    {
        //printf("Error opening the file.\n");
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