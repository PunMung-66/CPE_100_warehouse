#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int ShowStock() {
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    char header[100];
    char c;
    fgets(header, sizeof(header), file);

    printf("%-5s%-5s%-15s%-10s%-10s\n", "Code", "Unit", "Name", "Initial", "Sell");
    char code[5];
    int unit;
    char name[20];
    float initial, sell;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        printf("%-5s%-5d%-15s%-10.2f%-10.2f\n", code, unit, name, initial, sell);
    }

    fclose(file);
}

int cashier()
{
    char option;
    int option_out;
    printf("\n\n=== Welcome to (Cashier Menu) ===\n\n");
    printf("(1) Add order\n");
    printf("(2) Edit order\n");// can Clear specific order in Edit.
    printf("(3) Cancel order\n");// Cancel order
    printf("(4) Save order\n");
    printf("(5) Back(Main Menu) \n\n");
    printf("Choose your option:\n\n");
    printf("CPE_100:\\Menu\\Cashier> ");
    scanf(" %c", &option); //  add space for not read above newline.
    if (option < '1' || option > '5')
        option = '0';
    option_out = option - '0';
    return(option_out);
}