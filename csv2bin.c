#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "csv2bin.h"

void csv2bin() {
  char csvFileName[100];
  printf("Enter the CSV file name: ");
  scanf("%s", csvFileName);

  FILE *csvFile = fopen(csvFileName, "r");
  if (csvFile == NULL) {
    csv2bin();
  }
  // create binary file
  char binFileName[100];
  printf("Enter the BIN file name (or press Enter for default): ");
  char temp[2];
  fgets(temp, sizeof(temp), stdin);
  fgets(binFileName, sizeof(binFileName), stdin);
  binFileName[strcspn(binFileName, "\n")] = '\0';

  //default file name
  if (binFileName[0] == '\0') {
    strcpy(binFileName, csvFileName);
    char *dot = strrchr(binFileName, '.');
    if (dot != NULL) {
      *dot = '\0';
    }
    strcat(binFileName, "_result.bin");
  }
  else{
    strcat(binFileName, ".bin");
  }

  FILE *binFile = fopen(binFileName, "wb");
  if (binFile == NULL) {
    printf("Error creating binary file.\n");
    fclose(csvFile);
    return;
  }

  struct Product product;
  fscanf(csvFile, "%*[^\n]\n");

  while (fscanf(csvFile, "%[^,],%d,%[^,],%f,%f\n", product.code, &product.unit,
                product.name, &product.cost, &product.sell) == 5) {
    fwrite(&product, sizeof(struct Product), 1, binFile);
  }

  fclose(csvFile);
  fclose(binFile);

}