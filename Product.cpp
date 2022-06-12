#include "Product.h"
#include <iostream>

using namespace std;

void Product::print(void)
{
    cout << *this << endl;
}

std::ostream& operator<<(std::ostream& os, const Product& p)
{
    os << "*** product info ***" << endl;
    os << "{" << endl;
    os << "   id: " << p.id << endl;
    os << "   family: " << p.family << endl;
    os << "   name: " << p.name << endl;
    os << "   qtyAvail: " << p.qtyAvail << endl;
    os << "   qtySold: " << p.qtySold << endl;
    os << "   price: " << p.price << endl;
    os << "}" << endl;
    return os;
}
