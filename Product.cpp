#include "Product.h"
#include <iostream>

using namespace std;

void Product::print(void)
{
    cout << "*** product info ***" << endl;
    cout << "{" << endl;
    cout << "   id: " << id << endl;
    cout << "   family: " << family << endl;
    cout << "   name: " << name << endl;
    cout << "   qtyAvail: " << qtyAvail << endl;
    cout << "   qtySold: " << qtySold << endl;
    cout << "   price: " << price << endl;
    cout << "}" << endl;
}
