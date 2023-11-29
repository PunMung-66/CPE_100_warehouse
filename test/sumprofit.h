#include <stdio.h>
#include <stdlib.h>

double sumprofit = 0;

double netprofit(double profit) {
    FILE *csvFile;
    FILE *csvFile2;
    csvFile = fopen("profit.csv", "r");
    csvFile2 = fopen("temp.csv", "w");
    if (csvFile == NULL) {
        sumprofit += profit;
        fprintf(csvFile2, "%lf\n", profit);
        fclose(csvFile2);
        rename("temp.csv", "profit.csv");
        return 1; 
    }
    char line[100];
    fgets(line, sizeof(line), csvFile);
    if (line[0] == '\0') {
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
    rename("temp.csv", "profit.csv");
    printf("CSV file created successfully.\n");
}