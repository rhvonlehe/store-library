#ifndef STORE_H
#define STORE_H

#include "Product.h"
#include <vector>
#include <string>
#include <memory>
#include <thread>

class Store
{
public:

    enum Result
    {
        RESULT_SUCCESS,
        RESULT_SOLD_OUT
    };

    explicit Store(void);
    ~Store(void);

    std::vector<std::string> getProductFamilies(void);
    Product getProductInfo(std::string productId);
    Result purchaseProduct(std::string productId);
    std::vector<Product> getProductsInFamily(std::string family);

private:
    void saveReceipt(const Product& product) const;

    std::thread::id _customerId;

    struct Impl;  // PIMPL will prevent bleeding of json outside this class/lib
    std::unique_ptr<Impl>   _pimpl;
};


#endif
