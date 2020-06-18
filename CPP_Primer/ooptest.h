//Copyright C++Primer 15
//License BSD
//Author: Handling
//This is OOP test
#ifndef CPPPRIMER_OOPTEST_H
#define CPPPRIMER_OOPTEST_H

#include <string>
#include <iostream>
#include <set>
#include <memory>
namespace mynamespace {
class Quote {

 public:
  Quote() = default;
  Quote(const Quote &) = default;
  Quote(Quote&&) = default;
  Quote& operator=(const Quote &) = default;
  Quote& operator=(Quote&&) = default;
  virtual ~Quote() = default; //�������������ж�̬��
  Quote(const std::string &book, double sales_price)
	 : book_no_(book), price_(sales_price) {}



  std::string isbn() const { return book_no_; };

  virtual Quote* Clone() const & { return new Quote(*this); }
  virtual Quote* Clone() && { return new Quote(std::move(*this)); }
  virtual double net_price(std::size_t n) const
                 { return n * price_; }
 private:
  std::string book_no_;
 protected:
  double price_ = 0.0;

};

class DiscQuote : public Quote{
 public:
  DiscQuote() = default;
  DiscQuote(const std::string &book, double price, std::size_t qty, double disc): Quote(book, price), quantity_(qty), discount_(disc) {}

  double net_price(std::size_t) const = 0;

 protected:
  std::size_t quantity_ = 0;
  double discount_ = 0.0;
};


class Bulk_Quote : public DiscQuote {
 public:

  using DiscQuote::DiscQuote;  //�̳� DiscQuote�Ĺ��캯��
  double net_price(std::size_t) const override;

  Bulk_Quote *Clone() & { return new Bulk_Quote(*this); }
  Bulk_Quote *Clone() && { return new Bulk_Quote(std::move(*this)); }
 private:
  std::size_t min_qty_ = 0;  //ʹ���ۿ۵���͹�����
  double discount_ = 0.0;    //��С����ʾ���ۿ۶�
};


class Basket {
public:
  

  void AddItem(const Quote &sale)  {  items_.insert(std::shared_ptr<Quote>(sale.Clone())); }
  void AddItem(Quote &&sale) { items_.insert(std::shared_ptr<Quote>(std::move(sale).Clone())); }  //��sale����Ҳ����ֵ����,����������ֵ����

  double TotalReceipt(std::ostream &) const;
private:
  static bool Compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) 
  { return lhs->isbn() < rhs->isbn(); }

  // multset �����������,���� compare ��Ա����
  std::multiset<std::shared_ptr<Quote>, decltype(Compare)*> items_{Compare};
};

double print_total(std::ostream &os, const Quote &item, size_t n) ;
}



#endif // !CPPPRIMER_OOPTEST_H

