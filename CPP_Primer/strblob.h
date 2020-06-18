//Copyright c++primer 2020
//license  (BSD,GPL)
//Author : Handling
//This is Dynamically memory example

#ifndef CPPPRIMER_STRBLOB_H_
#define CPPPRIMER_STRBLOB_H_
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
namespace mynamespace {
 
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
bool operator==(const Blob<T> &, const Blob<T> &);

template <typename T> class Blob {

 friend class BlobPtr<T>;
 friend bool operator==<T>(const Blob<T> &, const Blob<T> &);
 public:
  using value_type = T;
  using size_type = typename std::vector<T>::size_type;
  //构造函数
  Blob() : data_(std::make_shared<std::vector<T>>()) {}
  Blob(std::initializer_list<T> il);
  
  //Blob 的元素数量
  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }

  //添加与删除元素
  
  void push_back(const T &t) { data_->push_back(t); }
  void push_back(T &&t) { data_->push_back(std::move(t)); }
  void pop_back();

  // 元素访问
  T& back();
  T& operator[](size_type i);

 private:
  std::shared_ptr<std::vector<T>> data_;
  void Check(size_type i, const std::string &msg) const;
};

template <typename T> class BlobPtr {
 public:
   BlobPtr(): curr_(0) {}
   BlobPtr(Blob<T> &a, size_t sz = 0) : wptr_(a.data_), curr_(sz) { }

   T& operator*() const { auto p = Check(curr_, "dereference past end"); return (*p)[curr_]; }
   
   BlobPtr& operator++();
   BlobPtr& operator--();
 private:
  std::shared_ptr<std::vector<T>> Check(std::size_t, const std::string &) const;
  std::weak_ptr<std::vector<T>> wptr_;
  std::size_t curr_;
};


class StrBlobPtr;
class StrBlob {

 friend StrBlobPtr;
 friend bool operator==(const StrBlob &loo, const StrBlob &roo); // loo :left operator object
 friend bool operator<(const StrBlob &loo, const StrBlob &roo);
 public:
  using size_type = std::vector<std::string>::size_type;

  StrBlob();
  StrBlob(std::initializer_list<std::string> il);
  std::string& operator[](std::size_t n);
  const std::string& operator[](std::size_t n) const;

  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }

  void PushBack(const std::string &t) { data_->push_back(t); }
  void PopBack();

  std::string& Front();
  std::string& Back();
  const std::string &Front() const;
  const std::string &Back() const;

  StrBlobPtr Begin();
  StrBlobPtr End();

 private:
   //检测函数 data_[i] 不合法 ，抛出异常
  void Check(size_type i, const std::string &msg) const;

  std::shared_ptr<std::vector<std::string>> data_;

};


class StrBlobPtr {

 friend bool operator==(const StrBlobPtr &loo, const StrBlobPtr &roo); // loo :left operator object
 friend bool operator<(const StrBlobPtr &loo, const StrBlobPtr &roo);
 friend StrBlobPtr operator+(const StrBlobPtr &loo, size_t n);
 friend StrBlobPtr operator-(const StrBlobPtr &loo, size_t n);
 public:
  StrBlobPtr(): curr(0) { }
  StrBlobPtr(StrBlob &a, size_t sz = 0)
	: weak_ptr_(a.data_), curr(sz) { }    

  StrBlobPtr operator++(int);
  StrBlobPtr operator--(int);
  StrBlobPtr& operator++();
  StrBlobPtr& operator--();
  std::string& operator*() const;
  std::string* operator->() const;

  std::string& DeRef() const;  //解引用
  StrBlobPtr& InCr();          //前缀递增

 private:
   std::shared_ptr<std::vector<std::string>>
	 Check(std::size_t, const std::string&) const;

   std::weak_ptr<std::vector<std::string>> weak_ptr_;
   std::size_t curr; 
};

bool operator==(const StrBlob &loo, const StrBlob &roo); // loo :left operator object
bool operator!=(const StrBlob &loo, const StrBlob &roo);
bool operator<(const StrBlob &loo, const StrBlob &roo);

bool operator==(const StrBlobPtr &loo, const StrBlobPtr &roo); // loo :left operator object
bool operator!=(const StrBlobPtr &loo, const StrBlobPtr &roo);
bool operator<(const StrBlobPtr &loo, const StrBlobPtr &roo);
StrBlobPtr operator+(const StrBlobPtr &loo,size_t n);
StrBlobPtr operator-(const StrBlobPtr &loo, size_t n);


class StrBolbPtrPtr {
public:
  StrBlobPtr* operator->() const;
  StrBlobPtr& operator*() const;
private:
  StrBlobPtr* mem_ptr_;
};

template<typename T>
inline Blob<T>::Blob(std::initializer_list<T> il) try: data_(std::make_shared<std::vector<T>>(il)) {
  
} catch(const std::bad_alloc &e) { ;//处理内存异常

}

template <typename T>
inline void Blob<T>::pop_back() {
  Check(0, "pop back on empty Blob");
  data_->pop_back();
}

template<typename T>
inline T &Blob<T>::back() {
  Check(0, "back on empty Blob");
  return data_->back();
}

template<typename T>
inline T &Blob<T>::operator[](size_type i) {
  Check(i, "subscript out of range");
  return (*data_)[i];
}

template<typename T>
inline void Blob<T>::Check(size_type i, const std::string &msg) const {
  if (i >= data_->size())
	throw std::out_of_range(msg);
}

template<typename T>
inline BlobPtr<T> &BlobPtr<T>::operator++() {
  
  Check(curr_, "curr is end");
  ++ curr_;
  return *this;
}

}

#endif // !CPPPRIMER_STRBLOB_H_