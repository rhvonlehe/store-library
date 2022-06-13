#ifndef JSONCONVERTUTILS_H
#define JSONCONVERTUTILS_H

#include "Product.h"
#include <nlohmann/json.hpp>

namespace sl
{
// This is a private header file, not to be part of the library's public interface
void to_json(nlohmann::json& j, const Product& p);
void from_json(const nlohmann::json& j, Product& p);

}
#endif // JSONCONVERTUTILS_H
