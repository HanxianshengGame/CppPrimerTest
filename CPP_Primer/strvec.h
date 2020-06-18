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

  static std::allocator<std::string> alloc;   //�����ڴ�
  
  std::string* elements_; //������ʼλ��
  std::string* first_free_; //��ǰ����Ԫ�ص�ĩβ����һ���ڴ����λ��
  std::string* cap;        //�����ڴ�ռ�β��λ��

  
};

bool operator==(const StrVec &loo, const StrVec &roo);
bool operator!=(const StrVec &loo, const StrVec &roo);
}
#endif // !CPPPRIMER_STRVEC_H


