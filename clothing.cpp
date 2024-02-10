#include <string>
#include <set>
#include <iostream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : Product(category, name, price, qty)
{
  size_ = size;
	brand_ = brand; 
}

Clothing::~Clothing()
{
  //not needed
}

std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> keywords; 
  std::set<std::string> clothesName = parseStringToWords(convToLower(name_));
  std::set<std::string> clothesBrand = parseStringToWords(convToLower(brand_));
  keywords = setUnion(clothesName, clothesBrand);
  keywords.insert(convToLower(size_));
  return keywords; 
}

// bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return false;
// }


std::string Clothing::displayString() const
{
  std::string display = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";
  return display;
}



void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n"; 
}

// int main() {
//     std::cout<< "hi clothes" << std::endl;
//     return 0;
// }
