//Copyright C++Primer
//License BSD
//Author: Handling
//This is Message System 
#include "messagesystem.h"


namespace mynamespace {
  Message::Message(const Message &msg) {
	if(this == &msg)
	  return;

	AddToFolders(msg);
	this->folders_ =  msg.folders_;
	this->contents_ = msg.contents_; 
  }
  Message &Message::operator=(const Message &msg) {
	if(this == &msg)
	  return *this;

	RemoveFromFolders();
	AddToFolders(msg);
	this->folders_ = msg.folders_;
	this->contents_ = msg.contents_;
	return *this;
  }
  Message::Message(Message &&msg): contents_(std::move(msg.contents_)) {
	MoveFolders(&msg);
  }
  Message &Message::operator=(Message &&rhs) {
	if (this != &rhs) {
	  RemoveFromFolders();
	  contents_ = std::move(rhs.contents_);
	  MoveFolders(&rhs);
	}
	return *this;
  }
  Message::~Message() {
	RemoveFromFolders();
  }
  void Message::Save(Folder &f) {
	folders_.insert(&f);
	f.AddMsg(this);
  }

  void Message::Remove(Folder &f) {
	folders_.insert(&f);
	f.AddMsg(this);
  }

  void swap(Message &lhs, Message &rhs) {

	using std::swap;
	if (&rhs == &lhs)
	  return;

	for (auto f: lhs.folders_)
	  f->RemoveMsg(&lhs);

	for (auto f: rhs.folders_)
	  f->RemoveMsg(&rhs);

    swap(lhs.folders_, rhs.folders_);
	swap(lhs.contents_, rhs.contents_);

	for(auto f: lhs.folders_)
	  f->AddMsg(&lhs);

	for (auto f : rhs.folders_)
	  f->AddMsg(&rhs);
  }

  void Message::RemoveFromFolders() {
	for (auto f : folders_) {
	  f->RemoveMsg(this);
	}
  }

  void Message::AddToFolders(const Message &msg) {
	for (auto f : msg.folders_) {
	  f->AddMsg(this);
	}
  }

  void Message::MoveFolders(Message *m) {
	folders_ = std::move(m->folders_);
	for (auto f : m->folders_) {
	  f->RemoveMsg(m);
	  f->AddMsg(m);
	}
	m->folders_.clear();
  }



  void Folder::AddMsg(Message *) {
  }

  void Folder::RemoveMsg(Message *) {
  }

}
