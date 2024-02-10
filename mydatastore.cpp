#include "util.h"
#include "mydatastore.h"
#include <map>
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    for (size_t i = 0; i < Products_vector.size(); ++i)
    {
        delete Products_vector[i];
    }
    Products_vector.clear();

    for (map<string, User*>::iterator it = Users_map.begin(); it != Users_map.end(); ++it)
    {
        delete it->second;
    }
    Users_map.clear();

    for (map<string, vector<Product*>>::iterator it = Carts_map.begin(); it != Carts_map.end(); ++it)
    {
        it->second.clear();
    }
    Carts_map.clear();
}

void MyDataStore::addProduct(Product* p)
{
  Products_vector.push_back(p);
  set<string> productKeywords = p->keywords();
  for (set<string>::iterator it = productKeywords.begin(); it != productKeywords.end(); ++it)
    {
      pair<map<string, set<Product*>>::iterator, bool> result = Keywords_set.insert(make_pair(*it, set<Product*>()));
      if (!result.second) 
      {
        result.first->second.insert(p);
      } 
      else 
      {
        result.first->second.insert(p);
      }
    }
}


void MyDataStore::addUser(User*u)
{
  Users_map[u->getName()] = u;
  Carts_map[u->getName()] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
  set<Product*> addedTerms;  
  for (vector<string>::iterator it = terms.begin(); it != terms.end(); it++)
  {
    set<Product*> mySet = Keywords_set[*it];

    if(type == 0)
    {
      if(it == terms.begin())
      {
        addedTerms = mySet; 
      }
      else
      {
        addedTerms = setIntersection<Product*> (addedTerms, mySet);
      }
    } 
    if(type == 1)
    {
      addedTerms = setUnion<Product*>(addedTerms, mySet); 
    }
  }

  vector<Product*> ans(addedTerms.begin(), addedTerms.end()); 
  return ans; 

}

void MyDataStore::dump(ostream &ofile)
{
  ofile << "<products>" << endl; 
  for(size_t i = 0; i < Products_vector.size(); i++)
  {
    Products_vector[i]->dump(ofile);
  }
  ofile << "</products>" << endl;
  ofile << "<users>" << endl;
  for(map<string,User*>::iterator it = Users_map.begin(); it != Users_map.end(); ++it)
  {
    Users_map[it->first]->dump(ofile);
  }
  ofile << "</users>" << endl;  ;
    
}

void MyDataStore::addCart(string user, Product* p)
{
  bool valid = false; 
  if(Users_map.find(user) != Users_map.end())
	{
		valid = true;
	}
  if(!valid)
  {
    std::cout << "Invalid request" << std::endl;
    return;
  }
  if(valid)
  {
    map<string, vector<Product*>>::iterator it = Carts_map.find(user);
    it->second.push_back(p);
  }
}

void MyDataStore::buyCart(string username)
{
	bool valid = false; 
  if(Users_map.find(username) != Users_map.end())
	{
		valid = true;
	}
  if(!valid)
  {
    cout << "Invalid Username" << endl; 
    return; 
  }
  
  map<string, User*>::iterator user = Users_map.find(username);
  map<string, vector<Product*>>::iterator itc = Carts_map.find(username);
  if (user == Users_map.end() || itc == Carts_map.end()) 
  {
    return;
  }
  User* currentUser = user->second;
  vector<Product*>& currentCart = itc->second;
  vector<Product*> remainingProducts;
  for (vector<Product*>::iterator itp = currentCart.begin(); itp != currentCart.end(); itp++) 
  {
    Product* product = *itp;
    if (product->getQty() > 0 && currentUser->getBalance() >= product->getPrice()) 
    {
      currentUser->deductAmount(product->getPrice());
      product->subtractQty(1);
    } 
    else 
    {
      remainingProducts.push_back(product);
    }
  }

  Carts_map[username] = remainingProducts;
}

void MyDataStore::viewCart(string user)
{
  bool valid = false; 
  if(Users_map.find(user) != Users_map.end())
	{
		valid = true;
	}
  if(!valid)
  {
    cout << "Invalid Username" << endl; 
    return; 
  }
  if(valid)
  {
    vector<Product*>& cart = Carts_map[user];
    int count = 1; 
    for (vector<Product*>::iterator it = cart.begin(); it != cart.end(); ++it)
    {
      cout << "Items: " << count << ". \n" << (*it)->displayString() << endl;
      count++;
    }

  }

}

bool MyDataStore::checkUser(string name){
  if(Users_map.find(name) != Users_map.end())
    return true;
  return false;

  
}