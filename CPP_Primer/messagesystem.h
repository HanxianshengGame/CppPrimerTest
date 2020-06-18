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
  Message(const Message&); //涉及到将自身添加到 右侧对象的 folders*，同时右侧对象的folder*也保存一份自身*拷贝
  Message& operator=(const Message&);  //将自身在其他folders的记录删除，更新自身 新folders*，同时右侧对象的folder*也保存一份自身*拷贝
  Message(Message&&);
  Message& operator=(Message&&);

  ~Message();// 将自身在其他folders的记录删除

  void Save(Folder&);
  void Remove(Folder&);


 private:

  void RemoveFromFolders();   // 将自身在其他folders的记录删除
  void AddToFolders(const Message&); //将自身添加到 右侧对象的 folders*
  void MoveFolders(Message* m);   //将m的folders*接管到自身

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

