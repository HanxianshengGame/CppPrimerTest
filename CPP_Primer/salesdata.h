
//Copyright 2020       
//License (BSD/GPL/...)       
//Author: Handling              
//This is CPPPrimer Study           

#ifndef CPPPRIMER_SALESDATA_H_
#define CPPPRIMER_SALESDATA_H_

#include <string>
#include <iostream>
#include "goolestyle.h"
namespace mynamespace {
class out_of_stock;
class isbn_mismatch;
class SalesData;
class SalesData {
 // 新成员: 关于 SalesData 对象的操作
 /*1.typedef 和 enums
   2.常量
   3.构造函数
   4.析构函数
   5.成员函数，含静态数据成员
   6.成员变量，含静态成员变量
   */
 friend SalesData Add(const SalesData &, const SalesData &);
 friend std::ostream &Print(std::ostream &, const SalesData &);
 friend std::istream &Read(std::istream &, SalesData &);
 friend SalesData&& operator+(const SalesData &lhs, const SalesData &rhs);
 friend std::istream& operator>>(std::istream &,SalesData&);
 friend std::ostream &operator<<(std::ostream &, SalesData &);

 public:


  SalesData(const std::string &book_no, unsigned unit_sold, double price) :
    book_no_(book_no), units_sold_(unit_sold), revenue_(price * unit_sold) {  }

  SalesData() : SalesData("",0,0) {}
  explicit SalesData(const std::string &s) : SalesData(s, 0, 0) {}
  explicit SalesData(std::istream &is) : SalesData()
                                     { Read(is,*this); }
  SalesData(const SalesData& orig);
  ~SalesData() = default;

  SalesData& operator=(const  std::string &ISBN);
  SalesData& operator+=(const SalesData &orig);



  std::string book_no() const { return book_no_; }
  SalesData& Combine(const SalesData &lhs);


 private:
  double AvgPrice() const
    { return units_sold_ ? revenue_/units_sold_ : 0; }
  std::string book_no_;
  unsigned units_sold_ = 0;
  double revenue_ = 0.0;
  static constexpr char period = '1';
//  DISALLOW_COPY_AND_ASSIGN(SalesData);
};
SalesData Add(const SalesData &lhs, const SalesData &rhs);
std::ostream &Print(std::ostream &, const SalesData &);
std::istream &Read(std::istream &, SalesData &);
SalesData&& operator+(const SalesData &lhs, const SalesData &rhs);
bool operator==(const SalesData&, const SalesData&); //在程序中用到的函数需要被定义, 且在头文件中定义的函数需要被内联
bool operator==(SalesData &, SalesData &);

std::istream &operator>>(std::istream &, SalesData &);
std::ostream &operator<<(std::ostream &, SalesData &);



class out_of_stock : public std::runtime_error {
 public:
  explicit out_of_stock(const std::string &s): std::runtime_error(s) {}

};

class isbn_mismatch : public std::logic_error {  //逻辑错误
public:
  explicit isbn_mismatch(const std::string &s): std::logic_error(s) {}

  isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs)
    : std::logic_error(s), left(lhs), right(rhs) {}

  const std::string left, right;
};
















class String {

  friend std::ostream &operator<<(std::ostream &os, String &s);
  friend bool operator==(const String &loo, const String &roo);
  friend bool operator<(const String& loo, const String &roo);

 public:
  char& operator[](size_t n);
  const char& operator[](size_t n) const;

  
 private:
  char *str;
  size_t sz;
};

inline
std::ostream &operator<<(std::ostream &os, String &s) {
  for (size_t i = 0; i != s.sz; ++i) {
    os << *(s.str +i);
  }
  return os;
}
inline
bool operator==(const String &loo, const String &roo) {
  return (loo.str == roo.str) && (loo.sz == roo.sz);
}
inline
bool operator!=(const String &loo, const String &roo) {
  return !(loo == roo);
}
inline
bool operator<(const String &loo, const String &roo) {
  if (roo.sz == 0)
    return true;

  if(loo.sz == 0)
    return false;

  return strcmp(loo.str, roo.str) < 0;
  
 }
}





#endif // !CPPPRIMER_SALESDATA_H_

