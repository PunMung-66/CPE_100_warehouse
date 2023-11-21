#include "add_clear_editB.h"
#include "cashier_UI.h"

void cashier_system()
{
    combine_basket();
    showBasket();
    int cash_option = cashier();
    while (cash_option != 5)
    {
        system("cls");
        while ( cash_option == 0)
        {
            system("cls");
            printf("\n** Please try again, your option is out of defined. **\n");
            cash_option = cashier();
        }
        if ( cash_option == 1 )
        {
            system("cls");
            printf("\n[Add option]\n\n");
            addToBasket_system();
            combine_basket();
        }
        else if ( cash_option == 2)
        {
            system("cls");
            printf("\n[Edit option]\n");
            editToBasket_system();
            combine_basket();
            }
        else if ( cash_option == 3)
        {
            system("cls");
            //printf("\n[Clear option]\n");
            clear_basket();
            combine_basket();
            }
        else if ( cash_option == 4){system("cls");printf("\n[Calculate total]\n");}
        else if ( cash_option == 5){break;}
        showBasket();
        cash_option = cashier();
    }
    system("cls");
    printf("\n>>> Main Menu\n");
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
    //system("cls");
    int wel_option = welcome();
    while (wel_option != 3)
    {
        //system("cls");
        while ( wel_option == 0)
        {
            system("cls");
            printf("\n** Please try again, your option is out of defined. **\n");
            wel_option = welcome();
        }
        if ( wel_option == 1 ){system("cls");printf("\n>>> Cashier Menu\n\n");cashier_system();}
        else if ( wel_option == 2){system("cls");printf("\n>>> Warehouse Menu\n\n");}
        else if ( wel_option == 3){exit(0);}
        wel_option = welcome();
    }
}

int main()
{
    welcome_system();
    return (0);
}