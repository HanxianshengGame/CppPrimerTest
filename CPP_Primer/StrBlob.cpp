//Copyright c++primer 2020
//license  (BSD,GPL)
//Author : Handling
//This is Dynamically memory example
#include "strblob.h"
using std::vector;
using std::string;
using std::make_shared;
using std::out_of_range;
using std::initializer_list;
using std::runtime_error;
using std::out_of_range;
namespace mynamespace{
  StrBlob::StrBlob():data_(make_shared<vector<string>>()) {}
  StrBlob::StrBlob(initializer_list<string> il) :
	         data_(make_shared<vector<string>>(il)) {}

  std::string &StrBlob::operator[](std::size_t n) {
	return data_->at(n);
  }

  const std::string &StrBlob::operator[](std::size_t n) const {
	return data_->at(n);
  }

  void StrBlob::PopBack() {
	Check(0, "pop_back on empty StrBlob");
	data_->pop_back();
  }

  string &StrBlob::Front() {
    Check(0, "front on empty StrBlob");
	return data_->front();
  }

  string &StrBlob::Back() {
	Check(0, "back on empty StrBlob");
	return data_->back();
  }

  const string &StrBlob::Front() const {
	Check(0, "front on empty StrBlob");
	return data_->front();
  }

  const string &StrBlob::Back() const {
	Check(0, "back on empty StrBlob");
	return data_->back();
  }

  StrBlobPtr StrBlob::Begin() {
	  return StrBlobPtr(*this);
  }

  StrBlobPtr StrBlob::End() {
	return StrBlobPtr(*this, data_->size());
  }

  void StrBlob::Check(size_type i, const std::string &msg) const {
	if (i >= data_->size())
	  throw out_of_range(msg);
  }


  StrBlobPtr StrBlobPtr::operator++(int) {
	StrBlobPtr ret = *this;
	++*this;
	return ret;
  }

  StrBlobPtr StrBlobPtr::operator--(int) {
	auto ret = *this;
	--*this;
	return ret;
  }

  StrBlobPtr &StrBlobPtr::operator++() {
     Check(curr,"increment past end of StrBlobPtr");
	 ++curr;
	 return *this;
  }

  StrBlobPtr &StrBlobPtr::operator--() {
	Check(--curr, "decrement past begin of StrBlobPtr");
	return *this;
  }

  std::string &StrBlobPtr::operator*() const {
	return DeRef();
  }

  std::string *StrBlobPtr::operator->() const {
	return & this->operator*();
  }

  std::string &StrBlobPtr::DeRef() const {
	auto p = Check(curr, "dereference past end");
	return (*p)[curr];

  }

  StrBlobPtr &StrBlobPtr::InCr() {
	Check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
  }

  std::shared_ptr<std::vector<std::string>> StrBlobPtr::Check(std::size_t i, const std::string &msg) const {
	auto ret = weak_ptr_.lock();
	if(!ret)
	  throw runtime_error("unbound StrBlobPtr");
	if(i >= ret->size())
	  throw out_of_range(msg);
	return ret;
  }

  bool operator==(const StrBlob &loo, const StrBlob &roo) {
	return *loo.data_ == *roo.data_;
  }

  bool operator!=(const StrBlob &loo, const StrBlob &roo) {
	return !(loo == roo);
  }

  bool operator<(const StrBlob &loo, const StrBlob &roo) {
	return *loo.data_ < *roo.data_;
  }



  bool operator==(const StrBlobPtr &loo, const StrBlobPtr &roo) {
	return (loo.weak_ptr_.lock() == roo.weak_ptr_.lock()) && (loo.curr == roo.curr);
  }

  bool operator!=(const StrBlobPtr &loo, const StrBlobPtr &roo) {
	return !(loo == roo);
  }

  bool operator<(const StrBlobPtr &loo, const StrBlobPtr &roo) {
	if(loo.weak_ptr_.lock() != roo.weak_ptr_.lock())
	  throw std::invalid_argument("argument is not match£¡");

	return loo.curr < roo.curr;
  }

  StrBlobPtr operator+(const StrBlobPtr &loo, size_t n) {
	auto res_ptr = loo;
	res_ptr.curr += n;
	return res_ptr;
  }

  StrBlobPtr operator-(const StrBlobPtr &loo, size_t n) {
	auto res_ptr = loo;
	res_ptr.curr -= n;
	return res_ptr;
  }

  StrBlobPtr *StrBolbPtrPtr::operator->() const {
	return  & this->operator*();
  }

  StrBlobPtr &StrBolbPtrPtr::operator*() const {
	if (mem_ptr_ == nullptr)
	  throw runtime_error("Stack OverFlow");
	return *mem_ptr_;
  }

}
