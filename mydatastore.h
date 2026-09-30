#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore : public DataStore {

private: 
    //Container 1: User Index
    std::map<std::string, User*> users_; //stores username as key and the actual user as the value

    //Container 2: Keyword Index
    std::map<std::string, std::set<Product*>> findProducts_; //each keyword maps to the set of products that contain the keyword

    //Container 3: List of All Products
    std::set<Product*> listofProducts_;

    //Container 4: Cart
    std::map<std::string, std::vector<Product*>> carts_;

public:
    virtual ~MyDataStore(); //destructor
    MyDataStore(); //constructor
    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    virtual void dump(std::ostream& ofile);

    void addToCart (std::string username,Product* p);

    void viewCart (std::string username);

    void buyCart (std::string username);

};

#endif