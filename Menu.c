#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int cashier()
{
    char option;
    int option_out;
    printf("\n\n=== Welcome to (Cashier Menu) ===\n\n");
    printf("(1) Add order\n");
    printf("(2) Edit order\n");
    printf("(3) Clear order\n");
    printf("(4) Calculate total price\n");
    printf("(5) Back(Main Menu) \n\n");
    printf("Choose your option:\n");
    scanf(" %c", &option); //  add space for not read above newline.
    if (option < '1' || option > '5')
        option = '0';
    option_out = option - '0';
    return(option_out);
}

void cashier_system()
{
    int cash_option = cashier();
    while (cash_option != 5)
    {
        while ( cash_option == 0)
        {
            printf("\n** Please try again, your option is out of defined. **\n\n");
            cash_option = cashier();
        }
        if ( cash_option == 1 ){printf("Add option");}
        else if ( cash_option == 2){printf("Edit option");}
        else if ( cash_option == 3){printf("Clear option");}
        else if ( cash_option == 4){printf("Calculate total");}
        cash_option = cashier();
    }
    printf("Back to Main Menu");
    
}

int welcome()
{
    char option;
    int option_out;
    printf("\n\n=== Welcome to (Main Menu) ===\n\n");
    printf("(1) Cashier\n");
    printf("(2) Warehouse\n");
    printf("(3) Exit() \n\n");
    printf("Choose your option:\n");
    scanf("%s", &option);
    if (option < '1' || option > '3')
        option = '0';
    option_out = option - '0';
    return(option_out);
}

void welcome_system()
{
    int wel_option = welcome();
    while (wel_option != 3)
    {
        while ( wel_option == 0)
        {
            printf("\n** Please try again, your option is out of defined. **\n\n");
            wel_option = welcome();
        }
        if ( wel_option == 1 ){cashier_system();}
        else if ( wel_option == 2){printf("option 2");}
        wel_option = welcome();
    }
}

int main()
{
    welcome_system();
    return (0);
}