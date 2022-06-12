#include "Store.h"
#include "OSMutex.h"
#include "JsonConvertUtils.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>

using namespace std;
using namespace nlohmann;

const char* _storeFile = "store.json";
const char* _mutexName = "StoreFileMutex";

struct Store::Impl
{
    void import(void);
    void persist(void) const;

    json jsonModel;
    map<string, vector<Product>> products;
};

void Store::Impl::import(void)
{
    OSMutex mutex(_mutexName);
    ifstream i(_storeFile);

    i >> jsonModel;

    for (const auto& record : jsonModel)
    {
        json j = record;
        auto product = j.get<Product>();
        auto family = record["family"];
        products[family].push_back(product);
    }
}



Store::Store(void)
    : _pimpl(make_unique<Impl>())
{

}

vector<string> Store::getProductFamilies(void)
{
    _pimpl->import();


}


