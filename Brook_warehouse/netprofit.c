#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
double total[2] = {200.0, 500.0}; // total profit
double sumprofit=0;
double netprofit(double profit) {
	sumprofit+=profit;
}
int main() {
	netprofit(total[1]);
    printf("The net profit is %.2lf", sumprofit);
}
