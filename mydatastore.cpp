#include "util.h"
#include "mydatastore.h"

using namespace std;
 
    //Container 1: User Index
    //std::map<std::string, User*> users_; //stores username as key and the actual user as the value

    //Container 2: Keyword Index
    //std::map<std::string, std::set<Product*>> findProducts_; //each keyword maps to the set of products that contain the keyword

    //Container 3: List of All Products
    //std::set<Product*> listofProducts_;


MyDataStore::~MyDataStore() //destructor
{

}

MyDataStore::MyDataStore() //constructor
{

}

/**
* Adds a product to the data store
*/
void MyDataStore::addProduct(Product* p)
{
    std::set<std::string> pkeywords; //creates set of strings to hold the keywords of p (next line)
    pkeywords = p->keywords(); //retrieves keywords of the product
    listofProducts_.insert(p); //add product itself to the list

    for(std::set<std::string>::iterator it = pkeywords.begin(); it != pkeywords.end(); ++it){
        findProducts_[*it].insert(p); //adds p to the set of products of the keyword
    }

}

/**
* Adds a user to the data store
*/
void MyDataStore::addUser(User* u)
{
    std::string user_key = convToLower(u->getName()); //stores the lowercase username
    users_[user_key] = u; //stores the user in the map 
}

/**
* Performs a search of products whose keywords match the given "terms"
*  type 0 = AND search (intersection of results for each term) while
*  type 1 = OR search (union of results for each term)
*/
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    if(terms.size() == 0){ //checks to see if vector is empty
        
        vector<Product*> empty;
        return empty; //returns empty vector 
    }

    set<Product*> resultSet; //set holds search results
    resultSet = findProducts_[convToLower(terms[0])]; //finds the first search word's set of products and puts it in the result set
    set<Product*> listOfTerms; //temporarily holds one search word's products
    
    //combine each term's products, intersecting for AND and union for OR
    for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
        listOfTerms = findProducts_[convToLower(*it)];

        if(type == 0){ //AND search
            resultSet = setIntersection(resultSet, listOfTerms);
        }
        else{ //OR search
            resultSet = setUnion(resultSet, listOfTerms);
        }
    }

    vector<Product*> resultVector;

    //copy set into a vector to return
    for(std::set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it){
        resultVector.push_back(*it);
    }

    return resultVector;


    
}

/**
* Reproduce the database file from the current Products and User values
*/
void MyDataStore::dump(std::ostream& ofile)
{

}

