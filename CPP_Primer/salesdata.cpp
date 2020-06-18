//Copyright 2020       
//License (BSD/GPL/...)       
//Author: Handling              
//This is CPPPrimer Study    
#include "salesdata.h"
namespace mynamespace {

  constexpr char SalesData::period;
  SalesData::SalesData(const SalesData &orig)
      : book_no_(orig.book_no_), units_sold_(orig.units_sold_), revenue_(orig.revenue_) {}

  SalesData &SalesData::operator=(const  std::string &ISBN) {
    book_no_ = ISBN;
    return *this;
  }

  SalesData &SalesData::operator+=(const SalesData &rhs) {

    if (book_no() != rhs.book_no())
      throw isbn_mismatch("wrong isbns", book_no(), rhs.book_no());
    units_sold_ += rhs.units_sold_;
    revenue_ += rhs.revenue_;
    return *this;
  }

  SalesData& SalesData::Combine(const SalesData &rhs) {
    
    return *this += rhs;
}
 
  SalesData Add(const SalesData &lhs, const SalesData &rhs) {
    SalesData sum = lhs;
    sum.Combine(rhs);
    return sum;
  }

  std::ostream &Print(std::ostream &os, const SalesData &item) {
    os << item.book_no() << " " << item.units_sold_ << " "
       << item.revenue_ << " " << item.AvgPrice();
    return os;
  }

  std::istream& Read(std::istream &is, SalesData &item){
    double price = 0;
    is >> item.book_no_ >> item.units_sold_ >> price;
    item.revenue_ = price * item.units_sold_;
    return is;
  }
  SalesData&& operator+(const SalesData &lhs, const SalesData &rhs) {
    SalesData sum = lhs;
    sum.Combine(rhs);
    return std::move(sum);
  }
  std::istream &operator>>(std::istream &is, SalesData &item) {
    double price = 0;
    is >> item.book_no_ >> item.units_sold_ >> price;

    if(is)
      item.revenue_ = price * item.units_sold_;
    else 
      item = SalesData();
    return is;
  }
  std::ostream &operator<<(std::ostream &os, SalesData &item) {
    os << item.book_no() << " " << item.units_sold_ << " "
      << item.revenue_ << " " << item.AvgPrice();
    return os;
  }

  char &String::operator[](size_t n) {
    return str[n];
  }

  const char &String::operator[](size_t n) const {
    return str[n];
  }

}
