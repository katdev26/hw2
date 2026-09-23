#include "util.h"
#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

//constructor
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : Product(category, name, price, qty){
    isbn_ = isbn;
    author_ = author;
}

std::set<std::string> Book::keywords() const{

    set<std::string> s1;
    set<std::string> s2;
    set<std::string> unionSet;

    s1= parseStringToWords(author_);
    s2 = parseStringToWords(name_);
    unionSet = setUnion(s1, s2);


    unionSet.insert(isbn_);
    
    return unionSet;
}

std::string Book::displayString() const{

    std::ostringstream ss;

    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    string stringResult = ss.str();

    return stringResult;
}

void Book::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}