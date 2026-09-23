#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class Movie : public Product{

    private:
        std::string genre_;
        std::string rating_;

    public: 
        Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating); //constructor
        
        //copied over all three virtual function from product.h
        virtual std::set<std::string> keywords() const;
        virtual std::string displayString() const;
        virtual void dump(std::ostream& os) const;
         
};

#endif
