#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("Current date: %d-%d-%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    printf("Current time: %d:%d:%d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);

    return 0;
}