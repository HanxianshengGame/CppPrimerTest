//Copyright C++Primer
//License BSD
//Author: Handling
// This is ResourceClass example
#include "hasptr.h"
using std::string;
namespace mynamespace {
  HasPtr &HasPtr::operator=(const HasPtr &rhs) {
	++ *rhs.use_;
	if (--use_ == 0) {
	  delete ps_;
	  delete use_;
	}
	ps_ = rhs.ps_;
	i_ = rhs.i_;
	use_ = rhs.use_;
	return *this;
  }
  HasPtr::~HasPtr() {
	if (-- * use_ == 0) {
	  delete use_;
	  delete ps_;
	}
  }
  void swap(HasPtr &lhs, HasPtr &rhs) {
	using std::swap;
	swap(lhs.ps_, rhs.ps_);
	swap(lhs.i_, rhs.i_);
  }
}
