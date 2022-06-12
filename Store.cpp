#include "Store.h"
#include "OSMutex.h"
#include "JsonConvertUtils.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;
using namespace nlohmann;

const char* _storeFile = "store.json";
const char* _mutexName = "StoreFileMutex";

#if 1 // TODO remove - pimpl not needed if we don't store a model between calls?
struct Store::Impl
{
    void                            fileToJson(void);
    map<string, vector<Product>>    importByFamily(void);
    map<string, Product>            importById(void);
    void                            persist(void) const;

    json jsonModel;
};

void Store::Impl::fileToJson(void)
{
    OSMutex mutex(_mutexName);
    ifstream i;
    std::ios_base::iostate exceptionMask = i.exceptions() | std::ios::failbit;
    i.exceptions(exceptionMask);

    try
    {
        i.open(_storeFile);
    }
    catch(std::system_error& e)
    {
        cerr << "file open failure" << endl;
        cerr << e.code().message() << endl;
        exit(1);
    }

    i >> jsonModel;
}

map<string, vector<Product>> Store::Impl::importByFamily(void)
{
    map<string, vector<Product>> imported;
    fileToJson();

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
    fileToJson();

    for (const auto& record : jsonModel)
    {
        json j = record;

        auto product = j.get<Product>();
        auto id = record["id"];
        imported[id] = product;
    }

    return imported;
}
#endif


Store::Store(void)
    : _pimpl(make_unique<Impl>())
{
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


