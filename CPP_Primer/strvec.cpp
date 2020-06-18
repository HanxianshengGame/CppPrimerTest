//Copyright C++Primer
//License BSD
//Author: Handling
// This is Dynamic memory manage class
#include "strvec.h"
using std::invalid_argument;
namespace mynamespace {
  std::allocator<std::string> StrVec::alloc;

  StrVec::StrVec(const StrVec &rhs) {
	auto newData = AllocNCopy(rhs.elements_, rhs.first_free_);
	elements_ = newData.first;
	first_free_ = cap = newData.second;
  }
  StrVec& StrVec::operator=(const StrVec &rhs) {
	auto newData = AllocNCopy(rhs.elements_, rhs.first_free_);     //防止自赋值现象。
	Free(); 
	elements_ = newData.first;
	first_free_ = cap = newData.second;
	return *this;
  }
  StrVec &StrVec::operator=(StrVec &&s) noexcept {
	if (&s != this) {
	  Free();
	  elements_ = s.elements_;
	  first_free_ = s.first_free_;
	  cap = s.cap;
	  s.elements_ = s.first_free_ = s.cap = nullptr;
	}
	return *this;
  }
  StrVec &StrVec::operator=(std::initializer_list<std::string> il) {
    auto data = AllocNCopy(il.begin(), il.end());
	Free();
	elements_ = data.first;
	first_free_ = cap = data.second;
	return *this;
  }
  std::string &StrVec::operator[](size_t n) {
	return *(elements_+n);
  }
  const std::string &StrVec::operator[](size_t n) const {
	return *(elements_ + n);
  }
  StrVec::StrVec(StrVec &&s) noexcept  //移动构造函数不应该抛出异常
      : elements_(s.elements_), first_free_(s.first_free_), cap(s.cap) {
	s.elements_ = s.first_free_ = s.cap = nullptr;
  }
  StrVec::~StrVec() {
	Free();
  }
  void StrVec::PushBack(const std::string &elem) {
	CheckAlloc();
	alloc.construct(first_free_++, elem);
  }
  void StrVec::ReAllocate() {
	auto new_capacity = Size() ? 2*Size() : 1;

	auto new_data = alloc.allocate(new_capacity);
/*	auto dest = new_data;
	auto elem = elements_;

for (size_t i = 0; i != Size() ; ++i) {
	  alloc.construct(dest++, std::move(*elements_++));
	}*/
	
	auto last = std::uninitialized_copy(std::make_move_iterator(elements_), std::make_move_iterator(first_free_), new_data);
	Free();

	elements_ = new_data;
	first_free_ = last;
	cap = elements_ + new_capacity;
  }
  void StrVec::Free() {
	if (elements_) {
	  for (auto p = first_free_; p != elements_; )
		alloc.destroy(-- p);
	}
	alloc.deallocate(elements_, cap - elements_);
  }
  std::pair<std::string *, std::string *> StrVec::AllocNCopy(const std::string *b, const std::string *e) {
	auto data = alloc.allocate(e - b);
	return { data , std::uninitialized_copy(b, e,data)};
  }
  bool operator==(const StrVec &loo, const StrVec &roo) {
	  return (loo.elements_ == roo.elements_) && (loo.first_free_ == roo.first_free_) && (loo.cap == roo.cap);
  }
  bool operator<(const StrVec &loo, const StrVec &roo) {
	if (loo.elements_ != roo.elements_)
	  throw invalid_argument("argument is invalid！");


	return loo.first_free_ < roo.first_free_;
  }
  bool operator!=(const StrVec &loo, const StrVec &roo) {
	return !(loo != roo);
  }
}
