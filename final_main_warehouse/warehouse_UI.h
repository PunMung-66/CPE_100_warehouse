#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sumprofit.h"
#include "read_state.h"
#include "total.h"
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100
#define BUFFER_SIZE 100
#define CODE_WIDTH 11
#define UNIT_WIDTH 11
#define NAME_WIDTH 20
#define INITIAL_WIDTH 10
#define SELL_WIDTH 10

int ShowStocks();
void AddUnit();
void AddNewProduct();
void EditProduct();
void RemoveStock();
void ClearStock();

int UpdateStock() {
  char choice[100];
  int choice1=0,choice2=0,h=0;

  do {
    ShowStocks();
    printf("=== (Update Menu) ===\n\n"); printf("(1) Add Units\n");
    printf("(2) Add New Product\n");
    printf("(3) Edit\n");
    printf("(4) RemoveStock\n");
    printf("(5) ClearStock\n");
    printf("(6) Back(Warehouse Menu) \n\n");
    printf("Choose your option: ");
    scanf("%s", choice);
    system("cls");
    h=strlen(choice);
    if(h!=1){
      choice2=9;
    }
    if (choice[0] < '1' || choice[0] > '6' || h!=1)
      choice[0] = '0';
    choice1 = choice[0] - '0';
    switch (choice1) {

    case 1:
      printf("\n[Add option]\n\n");
      ShowStocks();
      printf("\n");
      AddUnit();
      break;
    case 2:
      printf("\n[AddNew option]\n\n");
      ShowStocks();
      printf("\n");
      AddNewProduct();
      break;
    case 3:
      printf("\n[Edit option]\n\n");
      ShowStocks();
      printf("\n");
      EditProduct();
      break;
    case 6:
      printf("\n>>> Warehouse Menu\n\n");
      break;
    case 4:
        printf("\n[Remove Stock option]\n\n");
        ShowStocks();
        printf("\n");
        RemoveStock();
        break;
    case 5:
        printf("\n[Clear Stock option]\n\n");
        ShowStocks();
        printf("\n");
        ClearStock();
        break;
    default:
      printf("Invalid choice. Try again.\n\n");
    }

  } while (choice1 != 6);

  return 0;
}

int ShowStocks() {
 FILE *file = fopen("Database.csv", "r");

    if (file == NULL) 
    {
        //printf("Error opening the file.\n");
        return 1;
    } 
    else 
    {
        char header[100];
        int choice;
        fgets(header, sizeof(header), file);
        printf("%-*s%-*s%-*s%-*s%-*s\n", 10, "Code", 15, "Unit", 15, "Name", 15, "Cost", 15, "Sell");
        char code[100];
        int unit;
        char name[100];
        float cost, sell;
        while (fscanf(file, "%10[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &cost, &sell) == 5) {
            printf("%-*s%-*d%-*s%-*.2f%-*.2f\n", 10, code, 15, unit, 15, name, 15, cost, 15, sell);
        }
        fclose(file);

    }
    printf("\n");
    return 0;
}

void AddUnit() {
  char targetCode[CODE_WIDTH];
  int additionalUnits = 0;

  printf("Enter product code to add units(Enter 0 for cancel): ");
  scanf("%s", targetCode);
  if (strcmp(targetCode, "0") == 0) {
    system("cls");
    return;
  }

  FILE *file = fopen("Database.csv", "r");
  FILE *tempFile = fopen("temp.csv", "w");

  if (file == NULL || tempFile == NULL) {
    printf("Error opening files.\n");
    return;
  }

  char header[BUFFER_SIZE];
  fgets(header, sizeof(header), file);
  fprintf(tempFile, "%s", header);

  char code[CODE_WIDTH];
  int unit, flagest = 0, flag = 0;
  char name[NAME_WIDTH];
  float initial, sell;

  while (fscanf(file, "%10[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial,
                &sell) == 5) {
    if (strcmp(code, targetCode) == 0) {
      while (additionalUnits <= 0) {
        printf("Enter the number of units to add: ");
        scanf("%d", &additionalUnits);
        if (additionalUnits <= 0) {
          printf("Invalid number\n");
        }
      }
      unit += additionalUnits;
      flagest = 1;
    } else {
      flag = 1;
    }
    fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
  }

  fclose(file);
  fclose(tempFile);

  remove("Database.csv");
  rename("temp.csv", "Database.csv");

  if (flagest == 1) {
    system("cls");
    printf("Units added successfully.\n\n");
  } else if (flagest == 0 && flag == 1) {
    printf("No product\n");
    return AddUnit();
  }
}
void AddNewProduct() {
  char newCode[CODE_WIDTH];
  int newUnit;
  char newName[NAME_WIDTH];
  float newInitial, newSell;
  printf("Enter the new product code(Enter 0 for cancel): ");
  if (scanf("%s", newCode) != 1) {
    printf("\n(* Invalid input for product code. *)\n\n");
    return ;
  }
  if (strcmp(newCode, "0") == 0) {
    system("cls");
    return;
  }
  FILE *file = fopen("Database.csv", "r");
  if (file != NULL) {
    char code[CODE_WIDTH];
    while (fscanf(file, "%19[^,],", code) == 1) {
      fscanf(file, "%*[^\n]\n");

      if (strcmp(newCode, code) == 0) {
        fclose(file);
        printf("Product with the same code already exists.\n");
        return AddNewProduct();
      }
    } 

    fclose(file);
  } else {
    printf("Error opening the file.\n");
    return;
  }

  printf("Enter the number of units: ");
  if (scanf("%d", &newUnit) != 1 || newUnit < 0) {
    system("cls");
    printf("\n(* Invalid input for number of units. *)\n\n");
    return;
  }

  printf("Enter the product name: ");
  if (scanf("%s", newName) != 1) {
    system("cls");
    printf("\n(* Invalid input for product name. *)\n\n");
    return;
  }

  printf("Enter the initial price: ");
  if (scanf("%f", &newInitial) != 1 || newInitial < 0) {
    system("cls");
    printf("\n(* Invalid input for initial price. *)\n\n");
    return;
  }

  printf("Enter the sell price: ");
  if (scanf("%f", &newSell) != 1 || newSell < 0) {
    system("cls");
    printf("\n(* Invalid input for sell price. *)\n\n");
    return;
  }

  file = fopen("Database.csv", "a");
  if (file == NULL) {
    printf("Error opening the file.\n");
    return;
  }

  fprintf(file, "%s,%d,%s,%.2f,%.2f\n", newCode, newUnit, newName, newInitial,
          newSell);

  fclose(file);
  system("cls");
  printf("New product added successfully.\n\n");

}

void EditProduct() {
  char targetCode[CODE_WIDTH];
  char newName[NAME_WIDTH];
  int newUnit;
  float newInitial, newSell;

  printf("Enter the product code to edit (Enter 0 for cancel): ");
  scanf("%s", targetCode);
  if (strcmp(targetCode, "0") == 0) {
    system("cls");
    return;
  }

  FILE *file = fopen("Database.csv", "r");
  FILE *tempFile = fopen("temp.csv", "w");

  if (file == NULL || tempFile == NULL) {
    printf("Error opening files.\n");
    return;
  }

  char header[BUFFER_SIZE];
  fgets(header, sizeof(header), file);
  fprintf(tempFile, "%s", header);

  char code[CODE_WIDTH];
  int unit;
  char name[NAME_WIDTH];
  float initial, sell;

  int found = 0;

  while (fscanf(file, "%10[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial,
                &sell) == 5) {
    if (strcmp(code, targetCode) == 0) {
      printf("Current details for product %s:\n", targetCode);
      printf("Name: %s\n", name);
      printf("Enter new product name: ");
      scanf("%s", newName);

      printf("Enter new number of units: ");
      scanf("%d", &newUnit);
      if (newUnit < 0) {
        system("cls");
        printf("\n(* Invalid input. Number of units cannot be below 0. *)\n\n");
        return;}
      printf("Enter new initial price: ");
      scanf("%f", &newInitial);
      if (newInitial < 0) {
        system("cls");
        printf("\n(* Invalid input. Number of units cannot be below 0. *)\n\n");
        return;}

      printf("Enter new sell price: ");
      scanf("%f", &newSell);
      if (newSell < 0) {
        system("cls");
        printf("\n(* Invalid input. Number of units cannot be below 0. *)\n\n");
        return;}

      strcpy(name, newName);
      unit = newUnit;
      initial = newInitial;
      sell = newSell;

      found = 1;
    }
    fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
  }

  fclose(file);
  fclose(tempFile);

  remove("Database.csv");
  rename("temp.csv", "Database.csv");

  if (found) {
    system("cls");
    printf("Product %s edited successfully.\n\n", targetCode);
  } else {
    printf("Product %s not found.\n", targetCode);
    return EditProduct();
  }
}


typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    float quantity, initial, sell;
} product;


int menuwarehouse() {
    for(;;){
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
    
    printf("\n\n=== Welcome to (Warehouse Menu) ===\n\n(1) Update stock\n(2) Show stock\n(3) Net profit\n(4) Readstatement\n(5) Back(Main Menu)\n\n");


    for (int i = 0; i < numRecords; i++) {
        if (selling[i].quantity <= 4) {
            printf("::::-> (Alert!!) %s has only %.0f left!!\n", selling[i].name, selling[i].quantity);
        }
    }
    printf("\n");
    // Choose option
     int a, inputResult;

    while (1) {
        printf("Choose your option:\n\nCPE_100:\\Menu\\Warehouse>");
        inputResult = scanf(" %d", &a);
        if (inputResult == 1 && (a == 1 || a == 2 || a == 3 || a == 4 || a == 5)) {
            break; // Valid input, exit the loop
        } else {
            printf("Please input a valid number (1, 2, 3, 4 or 5)\n");  // Clear the input buffer
            while (getchar() != '\n');   // Keep reading characters until a newline is encountered
        }
    }
    printf("Selected option: %d\n", a);

    // Perform action based on the selected option
    if (a == 1) {
        system("cls");
        printf("\n[Update stock]\n\n");
        UpdateStock();
    } 
    else if (a == 2) {
        // Show stock
        system("cls");
        printf("\n[Show stock option]\n\n");
        ShowStocks();
    } 
    else if (a == 3) {
        system("cls");
        printf("\n[Show net profit]\n\n");
        printf("The net profit is %.2lf ", sumprofit);
    }
    else if (a == 4) {
        system("cls");
        printf("\n>>> [Read statement]\n\n");
        readstate();
  
    }
      else if (a == 5) {
        system("cls");
        printf("\n>>> Main Menu\n\n");
        break; 
    }
    }
}
void RemoveStock() {
    FILE *file = fopen("Database.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char header[BUFFER_SIZE];
    fgets(header, sizeof(header), file);
    fprintf(tempFile, "%s", header);

    char code[CODE_WIDTH];
    int unit;
    char name[NAME_WIDTH];
    float initial, sell;

    int found = 0;
    char targetCode[CODE_WIDTH];

    printf("Enter the product code to remove: ");
    scanf("%s", targetCode);

    while (fscanf(file, "%10[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        if (strcmp(code, targetCode) == 0) {
            found = 1;
            continue;
        }

        fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
    }

    fclose(file);
    fclose(tempFile);

    remove("Database.csv");
    rename("temp.csv", "Database.csv");

    if (found) {
        system("cls");
        printf("Product %s removed from stock.\n\n", targetCode);
    } else {
        printf("Product %s not found.\n", targetCode);
    }
}
void ClearStock() {
    FILE *file = fopen("Database.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    char header[BUFFER_SIZE];
    fgets(header, sizeof(header), file);
    fprintf(tempFile, "%s", header);

    char code[CODE_WIDTH];
    int unit;
    char name[NAME_WIDTH];
    float initial, sell;

    int found = 0;

    while (fscanf(file, "%10[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        if (unit == 0) {
            found = 1;
            continue;
        }

        fprintf(tempFile, "%s,%d,%s,%.2f,%.2f\n", code, unit, name, initial, sell);
    }

    fclose(file);
    fclose(tempFile);

    remove("Database.csv");
    rename("temp.csv", "Database.csv");

    if (found) {
        system("cls");
        printf("Products with 0 quantity removed from stock.\n\n");
    } else {
        printf("No products with 0 quantity found.\n");
    }
}
