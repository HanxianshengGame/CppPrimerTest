#pragma once
//Copyright C++Primer
//License BSD
//Author: Handling
//This is Message System 

#ifndef CPPPRIMER_MESSAGESYSTEM_H
#define CPPPRIMER_MESSAGESYSTEM_H
#include <string>
#include <set>
namespace mynamespace {

class Folder;
class Message {
 friend void swap(Message &lhs, Message &rhs);
 public:
  explicit Message(const std::string &str = ""): contents_(str) { }
  Message(const Message&); //�漰����������ӵ� �Ҳ����� folders*��ͬʱ�Ҳ�����folder*Ҳ����һ������*����
  Message& operator=(const Message&);  //������������folders�ļ�¼ɾ������������ ��folders*��ͬʱ�Ҳ�����folder*Ҳ����һ������*����
  Message(Message&&);
  Message& operator=(Message&&);

  ~Message();// ������������folders�ļ�¼ɾ��

  void Save(Folder&);
  void Remove(Folder&);


 private:

  void RemoveFromFolders();   // ������������folders�ļ�¼ɾ��
  void AddToFolders(const Message&); //��������ӵ� �Ҳ����� folders*
  void MoveFolders(Message* m);   //��m��folders*�ӹܵ�����

  std::string   contents_;
  std::set<Folder*>  folders_;
};
void swap(Message &lhs, Message &rhs);

class Folder {
 public:
  void AddMsg(Message*);
  void RemoveMsg(Message*);
private:
  std::set<Message*> msgs;
  
};
}
#endif // !CPPPRIMER_MESSAGESYSTEM_H

