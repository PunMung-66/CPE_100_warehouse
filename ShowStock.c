#include <stdio.h>

int ShowStock() {
    FILE *file = fopen("Database.csv", "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }
    char header[100];
    char c;
    fgets(header, sizeof(header), file);

    printf("%-5s%-5s%-15s%-10s%-10s\n", "Code", "Unit", "Name", "Initial", "Sell");
    char code[5];
    int unit;
    char name[20];
    float initial, sell;

    while (fscanf(file, "%5[^,],%d,%20[^,],%f,%f\n", code, &unit, name, &initial, &sell) == 5) {
        printf("%-5s%-5d%-15s%-10.2f%-10.2f\n", code, unit, name, initial, sell);
    }

    fclose(file);
    while(c!='Y'){
    printf("Do you want to go back to menu??(Y/N)");
    scanf(" %c",&c);
    if(c=='Y'||c=='y'){
        printf("hoolay");//menu function here :D
        break;
    }else{}
    }
}
int main(){
    ShowStock();
}