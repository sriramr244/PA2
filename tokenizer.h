#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<sstream>
struct token{
  std::string Content;
  std::string Type;
  bool last = false;
};

class tknzr{
  public:
  std::string str;
  std::string A_str;
  bool contr_assi;
  tknzr(std::string formula_str){
    str = formula_str;
    }
  bool tokenize_formula(std::vector<token> &f_toks);
 //bool tokenize_assignment(std::map<std::string, bool> &a_toks);
  void print_tokens(std::vector<token>&f_toks);
};


#endif
