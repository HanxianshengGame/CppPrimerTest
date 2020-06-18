#pragma once
//Copyright C++Primer
//License BSD
//Author: Handling
// This is ResourceClass example
#ifndef CPPPRIMER_HASPTR_H_
#define CPPPRIMER_HASPTR_H_
#include <string>
namespace mynamespace {

class HasPtr {
 friend void swap(HasPtr&,HasPtr&);
 public:
  HasPtr(const std::string &s = std::string()) 
	 : ps_(new std::string(s)), i_(0), use_(new std::size_t(1)) { }

  HasPtr(const HasPtr &p)
      : ps_(p.ps_), i_(p.i_), use_(p.use_) { ++use_; }

  HasPtr& operator=(const HasPtr &);
  ~HasPtr();
 private:
   std::string *ps_;
   int           i_;
   std::size_t *use_; 
};

}
#endif // !CPPPRIMER_HASPTR_H_


