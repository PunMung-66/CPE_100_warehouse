// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

struct Product {
    char code[5];
    int unit;
    char name[100];
    float cost;
    float sell;
};

#endif // PRODUCT_H
