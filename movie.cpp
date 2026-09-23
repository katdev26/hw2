#include "util.h"
#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category,name,price,qty){
    
    genre_ = genre;
    rating_ = rating;
}

std::set<std::string> Movie::keywords() const{
    set <std::string> s1;
    
    s1 = parseStringToWords(name_);
    s1.insert(convToLower(genre_));
    

    return s1;

}

std::string Movie::displayString() const{
    std::ostringstream ss;

    ss << name_ << "\n" << "Genre: " << genre_ << " " << "Rating: " <<  rating_ << "\n" << fixed << setprecision(2) << price_ << " " << qty_ << " left.";
    std::string stringResult = ss.str();

    return stringResult;
}

void Movie::dump(std::ostream& os) const{
    os << category_ << "\n" << name_ << "\n" << fixed << setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}       
        


 