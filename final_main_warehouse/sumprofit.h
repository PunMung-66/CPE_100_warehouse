#include <stdio.h>
#include <stdlib.h>

double sumprofit = 0;

double netprofit(double profit) { //netprofit function
    FILE *csvFile;
    FILE *csvFile2;
    csvFile = fopen("profit.csv", "r"); //read profit file
    csvFile2 = fopen("temp.csv", "w"); //write temp file
    if (csvFile == NULL) { //if didn't create csvFile
        sumprofit += profit; 
        fprintf(csvFile2, "%lf\n", profit);
        fclose(csvFile2);
        rename("temp.csv", "profit.csv");
        return 1; 
    }
    char line[100];
    fgets(line, sizeof(line), csvFile);
    if (line[0] == '\0') { // if create CSV file
        fprintf(csvFile, "%lf\n", profit);
        fclose(csvFile);
        printf("CSV file created successfully.\n");
        return 0;
    }
    sumprofit = atof(line);
    sumprofit += profit;
    fprintf(csvFile2, "%lf\n", sumprofit);
    fclose(csvFile);
    fclose(csvFile2);
    remove("profit.csv"); 
    rename("temp.csv", "profit.csv"); //swap temp file to profit
    printf("CSV file created successfully.\n");
}