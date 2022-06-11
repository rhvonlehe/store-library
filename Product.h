#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product
{
public:
    Product();

private:
    std::string id;
    std::string family;
    std::string name;
    uint32_t    qtyAvail;
    uint32_t    qtySold;
    float       price;
};

#endif
