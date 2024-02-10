#include <string>
#include <set>
#include <iostream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product(category, name, price, qty)
{
  genre_ = genre;
	rating_ = rating; 
}

Movie::~Movie()
{
  //not needed
}

std::set<std::string> Movie::keywords() const
{
  std::set<std::string> keywords; 
  std::set<std::string> MovieName = parseStringToWords(convToLower(name_));
  std::set<std::string> MovieGenre = parseStringToWords(convToLower(genre_));
  keywords = setUnion(MovieName, MovieGenre);
  keywords.insert(convToLower(rating_));
  return keywords; 
}

// bool Movie::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return false;
// }


std::string Movie::displayString() const
{
  std::string display = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n";
  return display;
}



void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n"; 
}

// int main() {
//     std::cout<< "hi movie" << std::endl;
//     return 0;
// }
