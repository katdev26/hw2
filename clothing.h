#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Clothing : public Product{
    private:

        std::string size_;
        std::string brand_;

    public:
        Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand); //constructor

        //copied over all three virtual function from product.h
        virtual std::set<std::string> keywords() const;
        virtual std::string displayString() const;
        virtual void dump(std::ostream& os) const;
         
};

#endif
