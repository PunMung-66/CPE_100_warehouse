#include "add_clear_editB.h"
#include "warehouse_UI.h"
#include "cashier_UI.h"
#include "Sold.h"
#include "bin_csv.h"
#include "Add_statement.h"
#include "login.h"

void cashier_system()
{ 
    combine_basket(total);
    showBasket();
    int cash_option = cashier();
    while (cash_option != 5)
    {
        system("cls");
        while ( cash_option == 0)
        {
            system("cls");
            printf("\n(** Please try again, your option is out of defined. **)\n\n");
            combine_basket(total); //combine the basket
            showBasket();
            cash_option = cashier();
        }
        if ( cash_option == 1 ) //add option system
        {
            system("cls");
            printf("\n[Add option]\n\n");
            addToBasket_system();
            combine_basket(total);
        }
        else if ( cash_option == 2) //edit option system
        {
            system("cls");
            printf("\n[Edit option]\n");
            editToBasket_system();
            combine_basket(total);
            }
        else if ( cash_option == 3) //clear basket system
        {
            system("cls");
            clear_basket();
            combine_basket(total);
            }
        else if ( cash_option == 4) //save basket system
        {
            system("cls");
            printf("\n[Save & Sold]\n");
            add_statement(total[0], total[1]);
            Sold();
            netprofit(total[1]);
            clear_basket();
            }
        else if ( cash_option == 5){break;} 
        showBasket();
        cash_option = cashier();
    }
    system("cls");
    system("cls");
    printf("\n>>> Main Menu\n");
}

int welcome()
{
    char option[10];
    int option_out;
    printf("\n\n=== Welcome to (Main Menu) ===\n\n");
    printf("(1) Cashier\n");
    printf("(2) Warehouse\n");
    printf("(3) Exit() \n\n");
    printf("Choose your option:\n\n");
    printf("CPE_100:\\Menu> "); //option UI
    scanf("%s", option);
    if ((option[0] < '1' || option[0] > '3') || strlen(option) != 1)
        option[0] = '0';
    option_out = option[0] - '0';
    return(option_out);
}

void welcome_system()
{
    system("cls");
    int wel_option = welcome();
    while (wel_option != 3)
    {
        //system("cls");
        while ( wel_option == 0)
        {
            system("cls");
            printf("\n(** Please try again, your option is out of defined. **)\n\n");
            wel_option = welcome();
        }
        if ( wel_option == 1 ) //go to cashier
        {
            bin2csv();
            system("cls");
            printf("\n>>> Cashier Menu\n\n");
            cashier_system();
            csv2bin();
        }
        else if ( wel_option == 2) //go to warehouse
        {
            bin2csv();
            system("cls");
            system("cls");
            printf("\n>>> Warehouse Menu\n\n");
            menuwarehouse();
            csv2bin();
        }
        else if ( wel_option == 3){exit(0);} //exit
        wel_option = welcome();
    }
}

int main()
{   
    system("cls");
    loginall();
    netprofit(0);
    welcome_system();
    return (0);
}