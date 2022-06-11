#include "Store.h"
#include "OSMutex.h"
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using namespace nlohmann;

struct Store::Impl
{
    json model;
};

Store::Store(void)
    : pimpl(make_unique<Impl>())
{

}

vector<string> Store::getProductFamilies(void)
{
    readIn();


}



void Store::readIn(void)
{
    OSMutex mutex(_mutexName);
    ifstream i(_storeFile);

    i >> pimpl->model;


}
