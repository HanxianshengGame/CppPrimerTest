#pragma once
//Copyright C++Primer
//license (BSD)
//Author : Handling
//This is TextQuery program

#ifndef CPPPRIMER_TEXTQUERY_H_
#define CPPPRIMER_TEXTQUERY_H_
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <iostream>
#include <sstream>
#include <algorithm>
namespace mynamespace {

class QueryResult;
//文本查询
class TextQuery {
 public:
  using line_no =  std::vector<std::string>::size_type;
  TextQuery(std::ifstream &);
  QueryResult Query(const std::string &) const;
 private:
  std::shared_ptr<std::vector<std::string>> file_data_;          //所有的行内容
  std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;  //单词-行号
};   

//查询结果
class QueryResult {
 friend std::ostream& print(std::ostream &, const QueryResult &);
 public:
  QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p,std::shared_ptr<std::vector<std::string>> f)
     : sought_(s), line_nos_(p), file_(f) { }

  std::set<TextQuery::line_no>::iterator begin() const { return line_nos_->begin(); }

  std::set<TextQuery::line_no>::iterator end() const { return line_nos_->end(); }
  std::shared_ptr<std::vector<std::string>> file() const { return file_; }
 private:
  std::string sought_;  //单词
  std::shared_ptr<std::set<TextQuery::line_no>> line_nos_;  //其行号
  std::shared_ptr<std::vector<std::string>> file_;          //文件内容
};  


class QueryBase {
  friend class  Query;

 protected:
  using line_no = TextQuery::line_no;  
  virtual ~QueryBase() = default;

 private:
   //eval 返回放弃与 Query 匹配的 QueryResult
  virtual QueryResult Eval(const TextQuery &) const = 0;
  //查询string
  virtual std::string Rep() const = 0;
};

class Query {
 friend Query operator~(const Query &);
 friend Query operator|(const Query &, const Query &);
 friend Query operator&(const Query &, const Query &);
public:
  Query(const std::string &);
  QueryResult Eval(const TextQuery &t) const { return q_->Eval(t); }
  std::string Rep() const { return q_->Rep(); }
private:
  Query(std::shared_ptr<QueryBase> query) :q_(query){}
  std::shared_ptr<QueryBase> q_;
};

//单词查询
class WordQuery: public QueryBase{
  friend class Query;
  WordQuery(const std::string &s): query_word_(s) {}
  QueryResult Eval(const TextQuery &t) const override { return t.Query(query_word_); }
  std::string Rep() const override { return query_word_; }
  std::string query_word_;
};
//非条件查询
class NotQuery : public QueryBase {
  friend Query operator~(const Query &);
  NotQuery(const Query &q): query(q) { } 
  std::string Rep() const override { return "~("+ query.Rep() + ")"; }
  QueryResult Eval(const TextQuery &) const override;

  Query query;
};


class BindaryQuery: public QueryBase {

 protected:
  BindaryQuery(const Query &l, const Query &r, std::string s)
    : lhs_(l), rhs_(r), oper_stym_(s) {}

  std::string Rep() const override { return "(" + lhs_.Rep() + " " + oper_stym_ + " " +rhs_.Rep() + ")"; }

  Query lhs_, rhs_;
  std::string oper_stym_;
};

//并条件查询
class AndQuery: public BindaryQuery{

  friend Query operator&(const Query &, const Query &);

  AndQuery(const Query &left, const Query &right): BindaryQuery(left, right, "&") {}

  QueryResult Eval(const TextQuery &) const override;
};

//或条件查询
class OrQuery : public BindaryQuery {

  friend Query operator|(const Query &, const Query &);

  OrQuery(const Query &left, const Query &right) : BindaryQuery(left, right, "|") {}

  QueryResult Eval(const TextQuery &) const override;
};

std::ostream &operator<<(std::ostream &os, const Query &query);

std::ostream &print(std::ostream &os, const QueryResult &qr); 


inline 
Query::Query(const std::string &s) : q_(new WordQuery(s)) {
  
}

inline 
Query operator~(const Query &operand) {
  return std::shared_ptr<QueryBase>(new NotQuery(operand));
}
inline
Query operator&(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new AndQuery(lhs, rhs));
}
inline
Query operator|(const Query &lhs, const Query &rhs) {
  return std::shared_ptr<QueryBase>(new OrQuery(lhs, rhs));
}
}
#endif // !CPPPRIMER_TEXTQUERY_H_
