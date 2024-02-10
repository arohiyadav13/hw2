#include <string>
#include <set>
#include <iostream>
#include <iomanip>
#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : Product(category, name, price, qty)
{
  author_ = author;
  isbn_ = isbn; 
}

Book::~Book()
{
  //not needed
}

std::set<std::string> Book::keywords() const
{
  std::set<std::string> keywords; 
  std::set<std::string> bookName = parseStringToWords(convToLower(name_));
  std::set<std::string> bookAuthor = parseStringToWords(convToLower(author_));
  keywords = setUnion(bookName, bookAuthor);
  keywords.insert(isbn_);
  return keywords; 
}

// bool Book::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return false;
// }


std::string Book::displayString() const
{
  std::string display = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";
  return display;
}



void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
}

// int main() {
//     std::cout<< "hi" << std::endl;
//     return 0;
// }
