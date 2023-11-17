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

void cashier_system()
{
    int cash_option = cashier();
    while (cash_option != 5)
    {
        system("cls");
        while ( cash_option == 0)
        {
            system("cls");
            printf("\n** Please try again, your option is out of defined. **\n\n");
            cash_option = cashier();
        }
        if ( cash_option == 1 ){printf("\n[Add option]");}
        else if ( cash_option == 2){printf("\n[Edit option]");}
        else if ( cash_option == 3){printf("\n[Clear option]");}
        else if ( cash_option == 4){printf("\n[Calculate total]");}
        cash_option = cashier();
    }
    system("cls");
    printf("\n>>> Main Menu");
}

int welcome()
{
    char option;
    int option_out;
    printf("\n\n=== Welcome to (Main Menu) ===\n\n");
    printf("(1) Cashier\n");
    printf("(2) Warehouse\n");
    printf("(3) Exit() \n\n");
    printf("Choose your option:\n\n");
    printf("CPE_100:\\Menu> ");
    scanf("%s", &option);
    if (option < '1' || option > '3')
        option = '0';
    option_out = option - '0';
    return(option_out);
}

void welcome_system()
{
    system("cls");
    int wel_option = welcome();
    while (wel_option != 3)
    {
        system("cls");
        while ( wel_option == 0)
        {
            system("cls");
            printf("\n** Please try again, your option is out of defined. **\n\n");
            wel_option = welcome();
        }
        if ( wel_option == 1 ){system("cls");printf("\n>>> Cashier Menu");cashier_system();}
        else if ( wel_option == 2){system("cls");printf("\n>>> Warehouse Menu");}
        wel_option = welcome();
    }
}

int main()
{
    welcome_system();
    return (0);
}