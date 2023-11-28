#include "bin2csv.h"
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bin2csv() {
  const char *binFileName = "Database.bin";
  const char *csvFileName = "Database.csv";

  FILE *binFile = fopen(binFileName, "rb");
  if (binFile == NULL) {
    printf("Error opening binary file.\n");
    return;
  }

  // Create CSV file
  FILE *csvFile = fopen(csvFileName, "w");
  if (csvFile == NULL) {
    printf("Error creating CSV file.\n");
    fclose(binFile);
    return;
  }

  struct Product product;

  fprintf(csvFile, "Code,Unit,Name,Cost(฿),Sell(฿)\n");

  // Write to CSV
  while (fread(&product, sizeof(struct Product), 1, binFile) == 1) {
    fprintf(csvFile, "%s,%d,%s,%.2f,%.2f\n", product.code, product.unit,
            product.name, product.cost, product.sell);
  }

  fclose(binFile);
  fclose(csvFile);

  printf("Binary to CSV conversion completed. CSV file: %s\n", csvFileName);

  // Delete the binary file
  remove(binFileName);
}
