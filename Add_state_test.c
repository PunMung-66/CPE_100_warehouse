#include <stdio.h>

int main()
{
    FILE *state_file = fopen("statement.csv", "w");
    fprintf(state_file, "%s,", "Total");
    fclose(state_file);
    return 0;
}