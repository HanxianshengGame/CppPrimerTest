//Copyright 2020 Google Inc.
//License ��BSD /GPL...��
//Author : Handling
//This is Google C++ Style
#include "goolestyle.h"         //�������������һ������ h�ļ�����Ч����������
#include <sys/types.h>          //c���ļ�
#include <vector>              //c++���ļ�
#include <string>
#include <iostream>
#include <cassert>
//#include "base/basictypes.h" �������ļ�
//#include "foo/public/bar.h"  ��ֹʹ��unix�ļ�·�� ��.�� �� ".."

using std::string;               //����������cc�ļ���h�ļ��ķ�����ʹ��using 
using std::cout;                //��ֹʹ��using namespace ��Ⱦ�����ռ�


namespace mynamespace {

    //���г�ʼ���б���:�� ǰ4�ո��������ԡ�,����β������������ж��룬���г�ʼ���б� 
    //Class::Class() : _var(xx) {}
    //���캯����ֻ������Щû��ʵ������ĳ�ʼ��
GoogleStyle::GoogleStyle()                   
    : num_entries_(10),
      num_complated_connections_(false) {
    
}

void GoogleStyle::Add(const std::string& input, //��������ʱ","��β��ÿ��һ����������
                      Channel* output) {
  bool retval = DoSomething(1, 2);           //�����У�","���һ����
  bool condition = false;
  
  if (condition) {                           //�����������޿ո�(condition)����һ�ո�ifִ�������ո�����
    for (int i = 0; i < kDaysInWeek; ++i) {  //ʹ��ǰ�õ��������
      if (i > i + 1 &&                        //������������ʱ��&&��β��������һ�������
          i + 3 == i + 4) {
          //TODO(name han1534930844@163.com): xxx ��ʱ����ʹ��TODO(��д)ע�ͣ�������ʹ�� ���ּ�����
      }
    }
  } else {                     //��������elseͬ�У�else���ҿո�
      auto j = GoogleStyle();  //����ʹ�ó�ʼ��ʱ����
  }
  switch (1) {                //(1)���Ҹ�1�ո�
    case 0: {                 //��������� switch 2������
      cout << "1";            //ִ���� 4������
      break;
    }
    default: { 
      assert(false);          //default����ִ��ʱʹ��assert
    }
  }
  return;                     //����ֵ����Ҫ������
}






bool DoSomething(int a, int b) {
  return false;
}

} // namespace mynamespace �����ռ����

/* 
1.������ʹ�ú�
2.��ʹ���쳣
3.��ֹʹ��RTTI
4.ʹ��printf֮��Ĵ�����
5.��λ��ʹ���޷�������
6.�����⻷������ʹ�ò���������
7.ʹ��4��cast���������ת��
8.��ֹʹ��  Class����ȫ�ֱ���
9.��ʹ�ñ���Ϊ����ģʽ
10.sizeof(var)����sizeof(type)
11.scoped_ptr ����ʤ������ָ��
12.��������¿���shared_ptr
13.�κ�ʱ��ʹ��auto_ptr
*/