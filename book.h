#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book : public Product
{
  public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
    ~Book();
    std::set<std::string> keywords() const;
    //isMatch(std::vector<std::string>& searchTerms) const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

  protected:
    std::string author_;
    std::string isbn_;
};
#endif