#include "user.h"
#include <vector>
#include <set>
#include <string>
#include <map>
#include "datastore.h"


class MyDataStore: public DataStore
{
  public:
    ///////
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User*u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    //////
    void addCart(std::string user, Product* p);
    void viewCart(std::string user);
    void buyCart(std::string user);
    bool checkUser(std::string name);
    
	
  protected:
    std::map<std::string, std::set<Product*>> Keywords_set;
    std::map<std::string, User*> Users_map;
    std::map<std::string, std::vector<Product*>> Carts_map;
    std::vector<Product*> Products_vector;

};
