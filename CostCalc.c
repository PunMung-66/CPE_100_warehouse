#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate(){
    FILE *basketFile = fopen("basket.txt", "a");

    if(basketFile == NULL){
        printf("Error opening the file.\n");
        return 0;
    }

}