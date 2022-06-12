#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    void print();

    std::string id;
    std::string family;
    std::string name;
    uint32_t    qtyAvail;
    uint32_t    qtySold;
    uint32_t    price;
};

#endif
