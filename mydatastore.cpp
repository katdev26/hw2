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
    for(std::set<Product*>::iterator it = listofProducts_.begin(); it != listofProducts_.end(); ++it){
        delete(*it);
    }

    for(std::map<std::string,User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        delete(it->second); 
    }
   
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
    ofile << "<products>" << endl;

    for(std::set<Product*>::iterator it = listofProducts_.begin(); it != listofProducts_.end(); ++it){
        (*it)->dump(ofile);
    }
   
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;

    for(std::map<std::string,User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        it->second->dump(ofile); //uses it->second to get the user
    }
   
    ofile << "</users>" << endl;

}

void MyDataStore::addToCart (std::string username,Product* p){
    
    std::string usernameKey = convToLower(username);
    if(users_.find(usernameKey) == users_.end()){ //check to see if invalid username
        cout << "Invalid request" << endl;
        return;
    }
    else{
        carts_[usernameKey].push_back(p); //adds product to the cart through FIFO
    }
    
}

void MyDataStore::viewCart (std::string username){
    
    std::string usernameKey = convToLower(username);
    if(users_.find(usernameKey) == users_.end()){ //check to see if invalid username
        cout << "Invalid username" << endl;
        return;
    }
    else{
        for(size_t i = 0; i < carts_[usernameKey].size(); i++){ //loops through items in the cart
            cout << "Item " << i+1 << endl; //i+1 is necessary so the first item is Item 1 and not Item 0
            cout << carts_[usernameKey][i]->displayString() << endl; //displays each item of the cart
        }
    }
    
}

void MyDataStore::buyCart (std::string username){
    
    std::string usernameKey = convToLower(username);

    if(users_.find(usernameKey) == users_.end()){ //check to see if invalid username
        cout << "Invalid username" << endl;
        return;
    }
    else{
        User* thisUser = users_[usernameKey]; //obtaining user's account to check and change balance
        vector<Product*> remainingProduct; //vector to store remaining product (products that can't be bought)

        for(size_t i = 0; i < carts_[usernameKey].size(); i++){ //loops through items in the cart
            Product* p = carts_[usernameKey][i]; //gets current product
            if(p->getQty() > 0 && p->getPrice() <= thisUser->getBalance()){
                p->subtractQty(1); //subtract one product from quantity since it is bought
                thisUser->deductAmount(p->getPrice()); //deduct's product's price from user's balance
            }
            else{
                remainingProduct.push_back(p);
            }
        }

        carts_[usernameKey] = remainingProduct; //only the items that weren't bought stay in the cart
    }
}
