//Copyright 2020 Google Inc.
//License （BSD /GPL...）
//Author : Handling
//This is Google C++ Style
#include "goolestyle.h"         //本类的声明（第一个包含 h文件，有效减少依赖）
#include <sys/types.h>          //c库文件
#include <vector>              //c++库文件
#include <string>
#include <iostream>
#include <cassert>
//#include "base/basictypes.h" 其他库文件
//#include "foo/public/bar.h"  禁止使用unix文件路径 “.” 和 ".."

using std::string;               //可以在整个cc文件和h文件的方法内使用using 
using std::cout;                //禁止使用using namespace 污染命名空间


namespace mynamespace {

    //多行初始化列表，“:” 前4空格缩进，以“,”结尾，多个变量折行对齐，单行初始化列表 
    //Class::Class() : _var(xx) {}
    //构造函数中只进行那些没有实际意义的初始化
GoogleStyle::GoogleStyle()                   
    : num_entries_(10),
      num_complated_connections_(false) {
    
}

void GoogleStyle::Add(const std::string& input, //参数过多时","结尾，每行一个变量对齐
                      Channel* output) {
  bool retval = DoSomething(1, 2);           //传参中，","后空一个格
  bool condition = false;
  
  if (condition) {                           //条件括号内无空格，(condition)左右一空格，if执行体两空格缩进
    for (int i = 0; i < kDaysInWeek; ++i) {  //使用前置递增运算符
      if (i > i + 1 &&                        //条件变量过多时，&&结尾，条件下一行左对齐
          i + 3 == i + 4) {
          //TODO(name han1534930844@163.com): xxx 临时方案使用TODO(大写)注释，括号里使用 名字加邮箱
      }
    }
  } else {                     //大括号与else同行，else左右空格
      auto j = GoogleStyle();  //尽量使用初始化时声明
  }
  switch (1) {                //(1)左右各1空格
    case 0: {                 //条件相对于 switch 2格缩进
      cout << "1";            //执行体 4格缩进
      break;
    }
    default: { 
      assert(false);          //default永不执行时使用assert
    }
  }
  return;                     //返回值不需要加括号
}






bool DoSomething(int a, int b) {
  return false;
}

} // namespace mynamespace 命名空间结束

/* 
1.尽量不使用宏
2.不使用异常
3.禁止使用RTTI
4.使用printf之类的代替流
5.除位域不使用无符号数字
6.除特殊环境，不使用操作符重载
7.使用4种cast运算符类型转换
8.禁止使用  Class类型全局变量
9.若使用必须为单例模式
10.sizeof(var)代替sizeof(type)
11.scoped_ptr 可以胜任智能指针
12.特殊情况下可用shared_ptr
13.任何时候不使用auto_ptr
*/