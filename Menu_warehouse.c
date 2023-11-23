#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100
#define BUFFER_SIZE 100
#define CODE_WIDTH 5
#define UNIT_WIDTH 5
#define NAME_WIDTH 15
#define INITIAL_WIDTH 10
#define SELL_WIDTH 10

int ShowStocks();
void AddUnit();
void AddNewProduct();
void EditProduct();

int UpdateStock() {
  char choice[100];
  int choice1=0,choice2=0,h=0;

  do {
    printf("=== (Update Menu) ===\n\n"); printf("(1) Add Units\n");
    printf("(2) Add New Product\n");
    printf("(3) Edit\n");
    printf("(4) Exit\n\n");
    printf("Choose your option: ");
    scanf("%s", choice);
    system("cls");
    h=strlen(choice);
    if(h!=1){
      choice2=9;
    }
    if (choice[0] < '1' || choice[0] > '4' || h!=1)
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
    case 4:
      printf("Exiting program.\n");
      break;
    default:
      printf("Invalid choice. Try again.\n\n");
    }

  } while (choice1 != 4);

  return 0;
}

int ShowStocks() {
  FILE *file = fopen("Database.csv", "r");

  if (file == NULL) {
    printf("Error opening the file.\n");
    return 1;
  } else {
    char header[BUFFER_SIZE];
    int choice;
    fgets(header, sizeof(header), file);
    printf("%-*s%-*s%-*s%-*s%-*s\n", CODE_WIDTH, "Code", UNIT_WIDTH, "Unit",
           NAME_WIDTH, "Name", INITIAL_WIDTH, "Cost", SELL_WIDTH, "Sell");

    char code[CODE_WIDTH];
    int unit;
    char name[NAME_WIDTH];
    float initial, sell;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name,
                  &initial, &sell) == 5) {
      printf("%-*s%-*d%-*s%-*.2f%-*.2f\n", CODE_WIDTH, code, UNIT_WIDTH, unit,
             NAME_WIDTH, name, INITIAL_WIDTH, initial, SELL_WIDTH, sell);
    }

    fclose(file);
  }
  return 0;
}

void AddUnit() {
  char targetCode[CODE_WIDTH];
  int additionalUnits = 0;

  printf("Enter product code to add units: ");
  scanf("%s", targetCode);

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

  while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial,
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
  printf("Enter the new product code: ");
  if (scanf("%s", newCode) != 1) {
    printf("Invalid input for product code.\n");
    return ;
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
    printf("Invalid input for number of units.\n");
    system("cls");
    return;
  }

  printf("Enter the product name: ");
  if (scanf("%s", newName) != 1) {
    printf("Invalid input for product name.\n");
    system("cls");
    return;
  }

  printf("Enter the initial price: ");
  if (scanf("%f", &newInitial) != 1 || newInitial < 0) {
    printf("Invalid input for initial price.\n");
    system("cls");
    return;
  }

  printf("Enter the sell price: ");
  if (scanf("%f", &newSell) != 1 || newSell < 0) {
    printf("Invalid input for sell price.\n");
    system("cls");
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

  printf("Enter the product code to edit: ");
  scanf("%s", targetCode);

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

  while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial,
                &sell) == 5) {
    if (strcmp(code, targetCode) == 0) {
      printf("Current details for product %s:\n", targetCode);
      printf("Name: %s\n", name);
      printf("Enter new product name: ");
      scanf("%s", newName);

      printf("Enter new number of units: ");
      scanf("%d", &newUnit);

      printf("Enter new initial price: ");
      scanf("%f", &newInitial);

      printf("Enter new sell price: ");
      scanf("%f", &newSell);

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
int ShowStocks();
void AddUnit();
void AddNewProduct();
void EditProduct();
typedef struct {
    char code[MAX_FIELD_SIZE], name[MAX_FIELD_SIZE];
    float quantity, initial, sell;
} product;
double total[2] = {200.0, 500.0}; // total profit
double sumprofit=0;
double netprofit(double profit) {
	sumprofit+=profit;
}

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
        UpdateStock();
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
        netprofit(total[1]);
        printf("The net profit is %.2lf ", sumprofit);
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
