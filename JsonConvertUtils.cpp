#include "JsonConvertUtils.h"

using namespace nlohmann;

void to_json(json& j, const Product& p)
{
    j = json{{"id", p.id}, {"family", p.family}, {"name", p.name},
    {"amountAvailable", p.qtyAvail}, {"amountSold", p.qtySold}, {"price", p.price}};
}


void from_json(const json& j, Product& p)
{
    j.at("id").get_to(p.id);
    j.at("family").get_to(p.family);
    j.at("name").get_to(p.name);
    j.at("amountAvailable").get_to(p.qtyAvail);
    j.at("amountSold").get_to(p.qtySold);
    j.at("price").get_to(p.price);
}
