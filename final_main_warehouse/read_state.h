#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Record {
    char day[50];
    char time[50];
    char code[50];
    int number;
    char name[50];
    double initial;
    double sell;
};

int isCommaLine(const char *line) {
    for (size_t i = 0; i < strlen(line); i++) {
        if (!isspace((unsigned char)line[i]) && line[i] != ',') {
            return 0;
        }
    }
    return 1;
}
//readstate
int readstate() {
    FILE *file = fopen("statement.csv", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening the file!\n");
        fclose(file);
        return 1;
    }

    struct Record records[100];
    int recordCount = 0;
    ssize_t read;

    char line[100];
    size_t lineSize = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (isCommaLine(line)) {
            continue;
        }

        struct Record record;

        int result = sscanf(line, "%49[^,],%49[^,],%49[^,],%d,%49[^,],%lf,%lf",
                            record.day, record.time, record.code, &record.number, record.name, &record.initial, &record.sell);

        // Check for the correct number of fields (7) and handle missing or empty fields
        if (result >= 4) {
            
            if (result < 5) {
                record.name[0] = '\0'; // Default value for missing "Name" field
            }

            // Add the record to the array
            records[recordCount++] = record;

            if (recordCount == 100) {
                break;
            }
        } else {
            fprintf(stderr, "Error parsing line: %s\n", line);
        }
    }

    fclose(file);
    int inp,a;
    while (1) {
        system("cls");
        printf("Choose\n\n(1) Date or (YYYY-MM-DD) \n(2) Month or (YYYY-MM)\n(3) Year: (YYYY)\n\nto input:");
        inp = scanf(" %d", &a);
        printf("\n");
        if (inp == 1 && (a == 1 || a == 2 || a == 3 )) {
            break; // Valid input, exit the loop
        } else {
            printf("Please input a valid number (1, 2 or 3)\n");  // Clear the input buffer
            while (getchar() != '\n');   // Keep reading characters until a newline is encountered
        }
    }

    if (a == 1) { 
    printf("Input date: ");
    int c=0;
    char date[50];
    scanf("%s", date);
    printf("\n");
    for (int i = 0; i < recordCount; i++) {
        if (strcmp(date, records[i].day) == 0 && strcmp("Total",records[i].code)!=0 ) {
            printf("Code: %s, Number: %d, Name: %s, Initial: %.2f, Sell: %.2f\n",
                   records[i].code, records[i].number, records[i].name, records[i].initial, records[i].sell);
                   c++;
        }
        if(strcmp("Total",records[i].code)==0 && strcmp(date, records[i].day) == 0 ){
            printf("%s,  %d,  profit, %.2f\n",
            records[i].code, records[i].number,records[i].sell);
            c++;
            printf("\n");
        }}
    if(c==0){
        printf("No information in that day");
    }
    }
    else if (a == 2) {
        printf("Input Month: ");
        char month[7]; // Adjust size for null terminator
        scanf("%7s", month); 
        int c=0;
        for (int i = 0; i < recordCount; i++) {
        if (strstr(records[i].day,month) && strcmp("Total",records[i].code)!=0){
             printf("Code: %s, Number: %d, Name: %s, Initial: %.2f, Sell: %.2f\n",
                   records[i].code, records[i].number, records[i].name, records[i].initial, records[i].sell);
                   c++;
        }
        if(strcmp("Total",records[i].code)==0 && strstr(records[i].day,month)){
            printf("%s,  %d,  profit, %.2f\n",
            records[i].code, records[i].number,records[i].sell);
            c++;
            printf("\n");
        }
        }
        if(c==0){
            printf("No information in that month");
        }
    }
    else if (a == 3) {
        printf("Input Year: ");
        char year[4]; // Adjust size for null terminator
        scanf("%4s", year); 
        int c=0;
        for (int i = 0; i < recordCount; i++) {
        if (strstr(records[i].day,year) && strcmp("Total",records[i].code)!=0){
             printf("Code: %s, Number: %d, Name: %s, Initial: %.2f, Sell: %.2f\n",
                   records[i].code, records[i].number, records[i].name, records[i].initial, records[i].sell);
                   c++;
        }
        if(strcmp("Total",records[i].code)==0 && strstr(records[i].day,year)){
            printf("%s,  %d,  profit, %.2f\n",
            records[i].code, records[i].number,records[i].sell);
            c++;
            printf("\n");
        }
        }
        if(c==0){
            printf("No information in that year");
        }
    }
  
  

    }

    
    



