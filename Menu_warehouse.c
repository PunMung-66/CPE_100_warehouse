#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100
typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    float quantity, initial, sell;
} product;
int menuwarehouse() {
    FILE *inputFile = fopen("Database.csv", "r");
    if (inputFile == NULL) {
        printf("Error opening the input CSV file\n");
        return 1;
    }
    product selling[MAX_RECORDS];
    int numRecords = 0;
    char line[MAX_FIELD_SIZE];
    // Skip the first line (header)
    fgets(line, sizeof(line), inputFile);

    while (fgets(line, sizeof(line), inputFile) && numRecords < MAX_RECORDS) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(selling[numRecords].code, token); //code
            token = strtok(NULL, ",");
            selling[numRecords].quantity = atof(token); //unit
            token = strtok(NULL, ",");
            strcpy(selling[numRecords].name, token); //name
            token = strtok(NULL, ",");
            selling[numRecords].initial = atof(token); //cost
            token = strtok(NULL, ",");
            selling[numRecords].sell = atof(token); //sell
            numRecords++;
        }
    }

    fclose(inputFile);
    

    // Print alert
    for(;;){
    printf("\n\n=== Welcome to (Warehouse Menu) ===\n\n(1) Update stock\n(2) Show stock\n(3) Net profit\n(4) Back(Main Menu)\n\n");
    for (int i = 0; i < numRecords; i++) {
        if (selling[i].quantity <= 4) {
            printf("(Alert!!) %s has only %.0f left!!\n", selling[i].name, selling[i].quantity);
        }
    }
    printf("\n");
    // Choose option
     int a, inputResult;

    while (1) {
        printf("Choose your option:\n\nCPE_100:\\Menu\\Warehouse>");
        inputResult = scanf(" %d", &a);
        if (inputResult == 1 && (a == 1 || a == 2 || a == 3 || a == 4)) {
            break; // Valid input, exit the loop
        } else {
            printf("Please input a valid number (1, 2, 3, or 4)\n");  // Clear the input buffer
            while (getchar() != '\n');   // Keep reading characters until a newline is encountered
        }
    }
    printf("Selected option: %d\n", a);

    // Perform action based on the selected option
    if (a == 1) {
        system("cls");
        printf("\n[Update stock]\n\n");

    } 
    else if (a == 2) {
        // Show stock
        system("cls");
        printf("\n[Show stock option]\n\n");
        printf("%-10s%-15s%-15s%-10s%-10s\n", "Code", "Quantity", "Name", "Cost", "Sell");
        for (int i = 0; i < numRecords; i++) {
            printf("%-10s%-15.2f%-15s%-10.2f%-10.2f\n", selling[i].code, selling[i].quantity, selling[i].name, selling[i].initial, selling[i].sell);
        }
    } 
    else if (a == 3) {
        system("cls");
        printf("\n[Show net profit]\n\n");
    }
    else if (a == 4) {
        system("cls");
        printf("\n>>> Main Menu\n\n");
        break; 
    }
    }
}
int main(){
menuwarehouse();   
}
