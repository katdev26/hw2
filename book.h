#ifndef BOOK_H
#define BOOK_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Book : public Product {
    private:

        std::string isbn_;
        std::string author_;

    public:
        Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author); //constructor

        //copied over all three virtual function from product.h
        virtual std::set<std::string> keywords() const;
        virtual std::string displayString() const;
        virtual void dump(std::ostream& os) const;
         
};

#endif