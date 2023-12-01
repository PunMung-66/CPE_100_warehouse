#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int loginall() {
    char username[20];
    char password[20];
    char correctUsername[] = "admin";
    char correctPassword[] = "1234";
    int attempts = 5;  // Number of login attempts allowed

    while (attempts > 0) {
        printf("Enter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            printf("Login successful!\n");
            break;  // Exit the loop if login is successful
        } else {
            attempts--;
            system("cls");
            printf("Login failed. Please check your username and password. %d attempts remaining.\n", attempts);
            if (attempts == 0) {
                printf("Sorry, you've run out of attempts. Account locked.\n");
                break;  // Exit the loop if no attempts are remaining
            }
        }
    }

}
