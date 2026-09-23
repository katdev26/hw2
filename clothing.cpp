#include "util.h"
#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

std::set<std::string> Clothing::keywords() const{
    set <std::string> s1;
    set <std::string> s2;
    set <std::string> unionSet;

    s1 = parseStringToWords(name_); //double check
    s2 = parseStringToWords(brand_);
    unionSet = setUnion(s1, s2);

    return unionSet;

}

std::string Clothing::displayString() const{
    std::ostringstream ss;

    ss << name_ << "\n" << "Size: " << size_ << " " << "Brand: " <<  brand_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    std::string stringResult = ss.str();

    return stringResult;
}

void Clothing::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}