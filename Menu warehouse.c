#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_FIELD_SIZE 100
#define MAX_RECORDS 100
typedef struct {
    char name[MAX_FIELD_SIZE];
    float quantity,initial,sell;
} product;
int menuwarehouse() {
    FILE *inputFile = fopen("database.csv", "r");
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
                selling[numRecords].quantity = atof(token);
                token = strtok(NULL, ",");
                strcpy(selling[numRecords].name, token);
                token = strtok(NULL, ",");
                selling[numRecords].initial = atof(token);
                token = strtok(NULL, ",");
                selling[numRecords].sell= atof(token);
                numRecords++;
            }
    }
    fclose(inputFile); //endof readfile
    int i;
    //start alert
    for(i=0;i < numRecords; i++){
    	if(selling[i].quantity<=4){
    		printf("%s has only %.0f left!!\n",selling[i].name,selling[i].quantity);
		}
	} //end of alert
	//start choosing what you want to do
    char a;
    char *ptr;
    for (;;) {
        printf("Please input your option:");
        scanf("%c", &a);
        if (a == '1' || a == '2' || a == '3' || a == '4' ) {
            ptr = &a;
            break;
        } else {
            printf("Please input a valid number\n");
        }
    }
    printf("Selected option: %c\n", *ptr);
     if (*ptr == '1') {
        printf("Update stock\n"); 
    } 
    if (*ptr == '2') { //show stock
	printf("            ==Welcome to Warehouse menu==\n");
    printf("Quantity       name                initial         sell\n");
    for (i = 0; i < numRecords; i++) {
    printf("%-15.2f%-20s%-15.2f%-15.2f\n" ,selling[i].quantity,selling[i].name, selling[i].initial, selling[i].sell);}
    printf("Choose your option\n");
    printf("(1) Update stock\n(2) show stock\n(3) Net profit\n(4) Exit\n");
    }
    if (*ptr == '3') {
        printf("Net profit\n");
    }
     if (*ptr == '4') {
        printf("Exit\n");
    }
    return 0;
}
