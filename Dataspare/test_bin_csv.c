#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Products {
    char code[5];
    int unit;
    char name[100];
    float cost;
    float sell;
};

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

  struct Products product_csv;

  fprintf(csvFile, "Code,Unit,Name,Cost(฿),Sell(฿)\n");

  // Write to CSV
  while (fread(&product_csv, sizeof(struct Products), 1, binFile) == 1) {
    fprintf(csvFile, "%s,%d,%s,%.2f,%.2f\n", product_csv.code, product_csv.unit,
            product_csv.name, product_csv.cost, product_csv.sell);
  }

  fclose(binFile);
  fclose(csvFile);

  printf("Binary to CSV conversion completed. CSV file: %s\n", csvFileName);

  // Delete the binary file
  remove(binFileName);
}

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

  struct Products product_bin;
  fscanf(csvFile, "%*[^\n]\n");

  while (fscanf(csvFile, "%[^,],%d,%[^,],%f,%f\n", product_bin.code, &product_bin.unit,
                product_bin.name, &product_bin.cost, &product_bin.sell) == 5) {
    fwrite(&product_bin, sizeof(struct Products), 1, binFile);
  }

  fclose(csvFile);
  fclose(binFile);

  printf("CSV to Binary conversion completed. Binary file: %s\n", binFileName);

  // Delete the CSV file
  remove(csvFileName);
}

int main() {
  int choice;
  printf("1. Convert binary to CSV\n");
  printf("2. Convert CSV to binary\n");
  printf("Enter your choice: ");
  scanf("%d", &choice);

  switch (choice) {
    case 1:
      bin2csv();
      break;
    case 2:
      csv2bin();
      break;
    default:
      printf("Invalid choice.\n");
      break;
  }

  return 0;
}

