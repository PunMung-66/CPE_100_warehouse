#include "csv2bin.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void csv2bin() {
  const char *csvFileName = "Database.csv";
  const char *binFileName = "Database.bin";

  FILE *csvFile = fopen(csvFileName, "r");
  if (csvFile == NULL) {
    printf("Error opening CSV file.\n");
    return;
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

  printf("CSV to Binary conversion completed. Binary file: %s\n", binFileName);

  // Delete the CSV file
  remove(csvFileName);
}
