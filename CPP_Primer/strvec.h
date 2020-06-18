#pragma once
//Copyright C++Primer
//License BSD
//Author: Handling
// This is Dynamic memory manage class
#ifndef CPPPRIMER_STRVEC_H
#define CPPPRIMER_STRVEC_H
#include <memory>
#include <string>
#include <utility>
#include <stdexcept>
namespace mynamespace {
class StrVec {

 friend bool operator==(const StrVec &loo, const StrVec &roo);
 friend bool operator<(const StrVec &loo, const StrVec &roo);
 public:
  StrVec(): elements_(nullptr), first_free_(nullptr), cap(nullptr) {}
  StrVec(const StrVec &);
  StrVec(StrVec &&) noexcept;
  StrVec& operator=(const StrVec &);
  StrVec& operator=(StrVec&&) noexcept;
  StrVec& operator=(std::initializer_list<std::string> il);
  std::string& operator[](size_t n);
  const std::string& operator[](size_t n) const;

  ~StrVec();

  void PushBack(const std::string &elem);
  size_t Size() { return first_free_ - elements_; }
  size_t Capacity() { return cap - elements_; }

  std::string *Begin() { return elements_; }
  std::string *End() { return first_free_; }
 
 private:
  void CheckAlloc() { if(Size() == Capacity())  ReAllocate(); }
  void ReAllocate();
  void Free();
  std::pair<std::string*,std::string*> AllocNCopy(const std::string *b,const std::string*e);

  static std::allocator<std::string> alloc;   //分配内存
  
  std::string* elements_; //数组起始位置
  std::string* first_free_; //当前数组元素的末尾，第一个内存空闲位置
  std::string* cap;        //数组内存空间尾后位置

  
};

bool operator==(const StrVec &loo, const StrVec &roo);
bool operator!=(const StrVec &loo, const StrVec &roo);
}
#endif // !CPPPRIMER_STRVEC_H


