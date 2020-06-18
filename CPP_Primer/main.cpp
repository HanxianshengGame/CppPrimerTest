//Copyright 2020 Handling
//License £¨BSD /GPL...£©
//Author : Handling
//This is C++Primer
#include "main.h"


using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ends;
using std::ostream;
using std::istringstream;
using std::ostringstream;
using std::vector;
using std::placeholders::_1;
using std::shared_ptr;
using std::make_shared;

using mynamespace::SalesData;
using mynamespace::StrBlob;
using mynamespace::StrBlobPtr;
using std::allocator;
using std::ifstream;
using mynamespace::TextQuery;
using mynamespace::Quote;
using mynamespace::Bulk_Quote;




bool valid(const std::smatch &);
int main(int argc,char **argv) {

  SalesData item1, item2, sum;
  while (cin >> item1 >> item2) {
	try {
	  sum = item1 + item2;
	} catch (const mynamespace::isbn_mismatch &e) {
	  cerr << e.what();
	}
  }

}



void print(const int ia[], size_t size) {
#ifndef NDEBUG
  cerr << __func__ << ": array size is " << size << endl;
#endif // !NDEBUG

}
