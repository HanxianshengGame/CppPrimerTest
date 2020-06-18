//Copyright 2008 Goole Inc.      版权
//License (BSD/GPL/...)          许可证
//Author: Handling               作者
//This is Google C++ Style                    文章描述

#ifndef CPPPRIMER_GOOLESTYLE_H_        //防止重复包含 宏格式为：<project>_<path>_<file>_
#define CPPPRIMER_GOOLESTYLE_H_  
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);              \
    TypeName& operator=(const TypeName&);

#include <vector>
#include <string>

class Channel;                //头文件中尽量使用前置声明 ,STL例外不适用前置声明，使用#include  
class Channel {

};
__interface CallbackInterface
{

}; 
namespace mynamespace {                       //命名空间全小写，顶头无空格，cc文件中提倡使用不具名命名空间
class GoogleStyle : public CallbackInterface {  //访问限定符1空格缩进，类名大写开头字母，使用组合                                              //比使用继承更加适宜，若用继承，只使用共有继承。
                                               //接口命名以 Interface结尾

 public:         
   /* 每一个限定符内，声明顺序如下
   1.typedef 和 enums
   2.常量
   3.构造函数
   4.析构函数
   5.成员函数，含静态数据成员
   6.成员变量，含静态成员变量
   */
  typedef std::vector<int> IntVector;                      //2空格缩进
  enum UrlTableErrors {                                    //枚举命名与类名相同，大写开头字母
    ERROR_OUT_OF_MEMORY = 0,                               //枚举值2格缩进，全大写下划线组合
    ERROR_MALFORMED_INPUT,
  };
  GoogleStyle();
  explicit GoogleStyle(const int xx);                      //explict修饰单参数构造函数，防止隐式转换误用
           	                                               //若定义了成员变量但是无其他构造函数，需要定义一个默认构造函数


//普通函数命名，大写开头单词，输入参数在前为const引用，输出参数在后为指针，不为参数设置缺省值
  void Add(const std::string& input, Channel* output);
  
  //存取函数命名，取：同变量名，村：值函数名为set_varname,短小的存取函数可用内联修饰
  int num_entries() const { return num_entries_; }  //尽可能使用const
  void set_num_entries(int num_entries) { num_entries_ = num_entries; }
 
 private:

  
   //仅在需要拷贝对象时使用拷贝构造函数(内部函数仍可以使用)，不需要拷贝时在使用DISALLOW_COPY_AND_ASSIGN宏
  DISALLOW_COPY_AND_ASSIGN(GoogleStyle);                                
  //变量要用描述性名称，不要节约空间，让别人理解你的代码更重要
  
  const int kDaysInWeek = 7;      //const 变量为k开头，后跟大写开头单词
  int num_entries_;               //变量命名：全小写，有意义的单词和下划线，类成员变量下划线结尾
  int num_complated_connections_;
 
  Channel* channel_;           //头文件中只用了指针/引用，则前向声明而非引入头文件
};


bool DoSomething(int a,int b);
} // namespace mynamespace
#endif // !CPPPRIMER_GOOLESTYLE_H  保护宏结尾加注释

