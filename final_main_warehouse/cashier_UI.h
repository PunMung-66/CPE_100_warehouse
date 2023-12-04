#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int cashier()
{
    char option[10];
    int option_out;
    printf("\n\n=== Welcome to (Cashier Menu) ===\n\n");
    printf("(1) Add order\n"); //add order
    printf("(2) Edit order\n");// can Clear specific order in Edit.
    printf("(3) Cancel order\n");// Cancel order
    printf("(4) Save order\n"); //save order
    printf("(5) Back(Main Menu) \n\n"); //back to main menu
    printf("Choose your option:\n\n"); 
    printf("CPE_100:\\Menu\\Cashier> ");//  add space for not read above newline.
    scanf("%s", option);
    if ((option[0] < '1' || option[0] > '5') || strlen(option) != 1)
        option[0] = '0';
    option_out = option[0] - '0';
    return(option_out);
}