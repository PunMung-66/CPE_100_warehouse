#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int welcome()
{
    int option;
    printf("=== Welcome to #main Menu ===\n\n");
    printf("(1) Cashier\n");
    printf("(2) Warehouse\n");
    printf("(3) Exit() \n\n");
    printf("Choose your option:\n");
    scanf("%d", &option);
    if (option < 1 || option > 3)
        option = 0;
    return(option);
}

void welcome_system()
{
    int wel_option = welcome();
    while ( wel_option == 0)
    {
        printf("\n** Please try again, your option is out of defined. **\n");
        wel_option = welcome();
    }
    if ( wel_option == 1 ){printf("option 1");}
    else if ( wel_option == 2){printf("option 2");}
    else if ( wel_option == 3){exit(1);}
    
}

int main()
{
    welcome_system();
    return (0);
}