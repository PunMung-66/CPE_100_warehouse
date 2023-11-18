#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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