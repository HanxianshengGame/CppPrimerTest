//Copyright C++Primer 15
//License BSD
//Author: Handling
//This is OOP test
#include "ooptest.h"
using std::endl;
namespace mynamespace {
  double Bulk_Quote::net_price(std::size_t cnt) const {
	if (cnt >= min_qty_)
	  return cnt * (1 - discount_) * price_;
	return cnt * price_;
  }
  double print_total(std::ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN:" << item.isbn() << " # sold: " << n << "total due: " << ret << endl;
	return ret;
  }
  double Basket::TotalReceipt(std::ostream &os) const {
	double sum = 0.0;
	
	for (auto iter = items_.cbegin(); iter != items_.cend(); iter = items_.upper_bound(*iter)) {

	  sum += print_total(os, **iter, items_.count(*iter));
	}

	return sum;
  }
}

