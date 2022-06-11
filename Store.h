#ifndef STORE_H
#define STORE_H

#include "Product.h"
#include <vector>
#include <string>
#include <memory>

class Store
{
public:

    enum Result
    {
        RESULT_SUCCESS,
        RESULT_SOLD_OUT
    };

    explicit Store(void);
    virtual ~Store(void) = default;

    std::vector<std::string> getProductFamilies(void);
    Product getProductInfo(std::string productId);
    Result purchaseProduct(std::string productId);
    std::vector<Product> getProducts(std::string family);

private:
    struct Impl;  // PIMPL will prevent bleeding of json into client

    std::unique_ptr<Impl>   pimpl;


    void readIn(void);
    void writeOut(void) const;

    const char* _storeFile = "store.json";
    const char* _mutexName = "StoreFileMutex";

};


#endif
