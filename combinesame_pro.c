#include <stdio.h>
#include <string.h>

void sort_order(char arr[100][40], int len)
{
    char *focus;
    for (int i = 1; i < len; i++)
    {
        strcpy(focus, arr[i]);
        int j = i - 1;

        while (j >= 0 && strcmp(arr[j], focus) > 0)
        {
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], focus);
    }
}

void combine_same_product_in_basket()
{
    FILE *basketFile = fopen("basket.txt", "r");
    //FILE *Tempfile = fopen("temp.txt", "w");
    if (basketFile == NULL ) {
        printf("Error opening basket file.\n");
        return;
    }
    char line[100];
    char store[100][40];
    int index = 0;
    while (fgets(line, sizeof(line), basketFile) != NULL)
    {
        strcpy(store[index], line);
        index++;
    }
    sort_order(store, index);
    // for (int i = 0; i < index; i++)
    // {

    // }
    // debugger
    index = 0;
    while (store[index][0])
    {
        printf("%s", store[index]);
        index++;
    }
    fclose(basketFile);
}

int main()
{
    combine_same_product_in_basket();
}