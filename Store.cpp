#include "Store.h"
#include "OSMutex.h"
#include "JsonConvertUtils.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <process.h>

namespace sl
{

using namespace std;
using namespace nlohmann;

const char* _storeFile = "store.json";
const char* _mutexName = "StoreFileMutex";

struct Store::Impl
{
    void                            fileToJson(void);
    void                            jsonToFile(void) const;
    map<string, vector<Product>>    importByFamily(void);
    map<string, Product>            importById(void);
    void                            updateModel(const Product& updated);

    json jsonModel;
};

void Store::Impl::fileToJson(void)
{
    ifstream i;
    std::ios_base::iostate exceptionMask = i.exceptions() | std::ios::failbit;
    i.exceptions(exceptionMask);

    try
    {
        i.open(_storeFile);
    }
    catch(std::system_error& e)
    {
        cerr << e.code().message() << endl;
        exit(1);
    }

    i >> jsonModel;
}

void Store::Impl::jsonToFile(void) const
{
    ofstream o;
    std::ios_base::iostate exceptionMask = o.exceptions() | std::ios::failbit;
    o.exceptions(exceptionMask);

    try
    {
        o.open(_storeFile);
    }
    catch(std::system_error& e)
    {
        cerr << e.code().message() << endl;
        exit(1);
    }

    o << std::setw(4) << jsonModel << endl;
}

map<string, vector<Product>> Store::Impl::importByFamily(void)
{
    map<string, vector<Product>> imported;

    {
        OSMutex mutex(_mutexName);
        fileToJson();
    }

    for (const auto& record : jsonModel)
    {
        json j = record;
        auto product = j.get<Product>();
        auto family = record["family"];
        imported[family].push_back(product);
    }

    return imported;   // nrvo
}

map<string, Product> Store::Impl::importById(void)
{
    map<string, Product> imported;

    {
        OSMutex mutex(_mutexName);
        fileToJson();
    }

    for (const auto& record : jsonModel)
    {
        json j = record;

        auto product = j.get<Product>();
        auto id = record["id"];
        imported[id] = product;
    }

    return imported;
}

void Store::Impl::updateModel(const Product& updated)
{
    json j = updated;

    for (auto& element : jsonModel)
    {
        if (element["id"] == j["id"])
        {
            element = j;
            break;
        }
    }
}


Store::Store(void)
    : _receiptNumber(0),
      _pimpl(make_unique<Impl>())
{
    _customerId = this_thread::get_id();
}

Store::~Store(void)
{
}

vector<string> Store::getProductFamilies(void)
{
    vector<string> families;

    auto imported = _pimpl->importByFamily();

    for (const auto& mapEntry : imported)
    {
        families.push_back(mapEntry.first);
    }

    return families;
}

Product Store::getProductInfo(string productId)
{
    auto imported = _pimpl->importById();

    return imported[productId];
}

Store::Result Store::purchaseProduct(string productId)
{
    Product bought;

    {
        OSMutex mutex(_mutexName);

        auto imported = _pimpl->importById();

        bought = imported[productId];

        if (bought.qtyAvail < 1)
        {
            return Store::RESULT_SOLD_OUT;
        }

        bought.qtyAvail--;
        bought.qtySold++;

        _pimpl->updateModel(bought);
        _pimpl->jsonToFile();
    }

    saveReceipt(bought);

    return Store::RESULT_SUCCESS;
}

vector<Product> Store::getProductsInFamily(std::string family)
{
    auto imported = _pimpl->importByFamily();

    return imported[family];
}

void Store::saveReceipt(const Product& product)
{
    ofstream o;
    std::ios_base::iostate exceptionMask = o.exceptions() | std::ios::failbit;
    o.exceptions(exceptionMask);

    stringstream nowStr, customerStr;
    customerStr << _customerId;
    _receiptNumber++;
    std::string receiptId = customerStr.str() + "-" + to_string(_receiptNumber);
    std::string receiptName = "receipt-" + receiptId;

    try
    {
        o.open(receiptName);
    }
    catch(std::system_error& e)
    {
        cerr << e.code().message() << endl;
        exit(1);
    }

    auto nowTimeT = chrono::system_clock::to_time_t(chrono::system_clock::now());
    nowStr << put_time(localtime(&nowTimeT), "%Y-%m-%d-%X");
    o << "Purchase made:" << endl;
    o << "by customer: " << _customerId << endl;
    o << product << endl;
    o << "at time: " << nowStr.str() << endl;
}

} // namespace sl

