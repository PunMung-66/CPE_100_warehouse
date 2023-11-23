#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "bin2csv.h"


void bin2csv() {
  char binFileName[100];
  printf("Enter the binary file name: ");
  scanf("%s", binFileName);

  FILE *binFile = fopen(binFileName, "rb");
  if (binFile == NULL) {
    bin2csv();
  }

  //create csv file
  char csvFileName[100];
  printf("Enter the CSV file name (or press Enter for default): ");
  char temp[2];
  fgets(temp, sizeof(temp), stdin);
  fgets(csvFileName, sizeof(csvFileName), stdin);
  csvFileName[strcspn(csvFileName, "\n")] = '\0';

  if (csvFileName[0] == '\0') {
    strcpy(csvFileName, binFileName);
    char *dot = strrchr(csvFileName, '.');
    if (dot != NULL) {
      *dot = '\0';
    }
    strcat(csvFileName, "_result.csv");
  }
  else{
    strcat(binFileName, ".bin");
  }

  FILE *csvFile = fopen(csvFileName, "w");
  if (csvFile == NULL) {
    printf("Error creating CSV file.\n");
    fclose(binFile);
    return;
  }

  struct Product product;

  fprintf(csvFile, "Code,Unit,Name,Cost(฿),Sell(฿)\n");

  // write to CSV
  while (fread(&product, sizeof(struct Product), 1, binFile) == 1) {
    fprintf(csvFile, "%s,%d,%s,%.2f,%.2f\n", product.code, product.unit,
            product.name, product.cost, product.sell);
  }

  fclose(binFile);
  fclose(csvFile);

}