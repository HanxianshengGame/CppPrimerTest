//Copyright C++Primer
//license (BSD)
//Author : Handling
//This is TextQuery program
#include "textquery.h"

using std::vector;
using std::string;
using std::istringstream;
using std::getline;
using std::make_shared;
using std::set;
using std::shared_ptr;
namespace mynamespace {
  TextQuery::TextQuery(std::ifstream &is):file_data_(make_shared<vector<string>>()) {
	string text;
	while (getline(is, text)) {
	  file_data_->push_back(text);
	  int n = file_data_->size() -1;
	  istringstream line(text);
	  string word;
	  while (line >> word) {
		auto &lines = wm[word];
		if(!lines)
		  lines.reset(new set<line_no>);

		lines->insert(n);
	  }
	}
  }
  QueryResult TextQuery::Query(const std::string &sought) const {
	static shared_ptr<set<line_no>> no_data(new set<line_no>);

	auto loc = wm.find(sought);
	if (loc != wm.end())
	  return QueryResult(sought, no_data, file_data_);
	else
	  return QueryResult(sought, loc->second, file_data_);
  }

  std::ostream &operator<<(std::ostream &os, const Query &query) {
	os << query.Rep();
	return os;
  }

  std::ostream &print(std::ostream &os, const QueryResult &qr) {
	os << qr.sought_ << " occurs " << qr.line_nos_->size()
	  << (qr.line_nos_->size() <= 1 ? "time" : "times") << std::endl;

	for (auto num : *qr.line_nos_)
	  os << "\t (line " << num + 1 << ") " << *(qr.file_->begin() + num) << std::endl;
	return os;
  }

  QueryResult OrQuery::Eval(const TextQuery &text) const {
	auto right = rhs_.Eval(text), left = lhs_.Eval(text);

	auto ret_lines = make_shared<set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());

	return QueryResult(Rep(), ret_lines, left.file());
  }

  QueryResult AndQuery::Eval(const TextQuery &text) const {
	auto right = rhs_.Eval(text), left = lhs_.Eval(text);
	auto ret_lines = make_shared<set<line_no>>();

	std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));

	return QueryResult(Rep(), ret_lines, left.file());
  }

  

  QueryResult NotQuery::Eval(const TextQuery &text) const {
	auto result = query.Eval(text);
	auto ret_lines = make_shared<set<line_no>>();

	auto beg = result.begin(), end = result.end();

	auto sz = result.file()->size();

	for (size_t n = 0; n != sz; ++n) {
	  if (beg != end && n == *beg) {
		++ beg;
		 continue;
	  }
	  ret_lines->insert(n);
	  
	}
	return QueryResult(Rep(), ret_lines, result.file());

  }

}
