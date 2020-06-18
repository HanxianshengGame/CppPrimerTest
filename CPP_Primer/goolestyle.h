//Copyright 2008 Goole Inc.      ��Ȩ
//License (BSD/GPL/...)          ���֤
//Author: Handling               ����
//This is Google C++ Style                    ��������

#ifndef CPPPRIMER_GOOLESTYLE_H_        //��ֹ�ظ����� ���ʽΪ��<project>_<path>_<file>_
#define CPPPRIMER_GOOLESTYLE_H_  
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&);              \
    TypeName& operator=(const TypeName&);

#include <vector>
#include <string>

class Channel;                //ͷ�ļ��о���ʹ��ǰ������ ,STL���ⲻ����ǰ��������ʹ��#include  
class Channel {

};
__interface CallbackInterface
{

}; 
namespace mynamespace {                       //�����ռ�ȫСд����ͷ�޿ո�cc�ļ����ᳫʹ�ò����������ռ�
class GoogleStyle : public CallbackInterface {  //�����޶���1�ո�������������д��ͷ��ĸ��ʹ�����                                              //��ʹ�ü̳и������ˣ����ü̳У�ֻʹ�ù��м̳С�
                                               //�ӿ������� Interface��β

 public:         
   /* ÿһ���޶����ڣ�����˳������
   1.typedef �� enums
   2.����
   3.���캯��
   4.��������
   5.��Ա����������̬���ݳ�Ա
   6.��Ա����������̬��Ա����
   */
  typedef std::vector<int> IntVector;                      //2�ո�����
  enum UrlTableErrors {                                    //ö��������������ͬ����д��ͷ��ĸ
    ERROR_OUT_OF_MEMORY = 0,                               //ö��ֵ2��������ȫ��д�»������
    ERROR_MALFORMED_INPUT,
  };
  GoogleStyle();
  explicit GoogleStyle(const int xx);                      //explict���ε��������캯������ֹ��ʽת������
           	                                               //�������˳�Ա�����������������캯������Ҫ����һ��Ĭ�Ϲ��캯��


//��ͨ������������д��ͷ���ʣ����������ǰΪconst���ã���������ں�Ϊָ�룬��Ϊ��������ȱʡֵ
  void Add(const std::string& input, Channel* output);
  
  //��ȡ����������ȡ��ͬ���������壺ֵ������Ϊset_varname,��С�Ĵ�ȡ����������������
  int num_entries() const { return num_entries_; }  //������ʹ��const
  void set_num_entries(int num_entries) { num_entries_ = num_entries; }
 
 private:

  
   //������Ҫ��������ʱʹ�ÿ������캯��(�ڲ������Կ���ʹ��)������Ҫ����ʱ��ʹ��DISALLOW_COPY_AND_ASSIGN��
  DISALLOW_COPY_AND_ASSIGN(GoogleStyle);                                
  //����Ҫ�����������ƣ���Ҫ��Լ�ռ䣬�ñ��������Ĵ������Ҫ
  
  const int kDaysInWeek = 7;      //const ����Ϊk��ͷ�������д��ͷ����
  int num_entries_;               //����������ȫСд��������ĵ��ʺ��»��ߣ����Ա�����»��߽�β
  int num_complated_connections_;
 
  Channel* channel_;           //ͷ�ļ���ֻ����ָ��/���ã���ǰ��������������ͷ�ļ�
};


bool DoSomething(int a,int b);
} // namespace mynamespace
#endif // !CPPPRIMER_GOOLESTYLE_H  �������β��ע��

