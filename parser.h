#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <map>
#include "tokenizer.h"
#include "treeNode.h"
#include <algorithm>
#include <vector>
struct parser_tree{
      bool error = false;
      TreeNode* tree_ptr = nullptr;
      
};

class formula_parser {
public:
std::vector <token> toks;
std::map <std::string, bool> as_toks;
std::string str, assignment;
token* tok_ptr;
token* tok_end;
bool tknzr_err = false;
bool as_tknzr_err = false;
bool contra_err = false;
formula_parser(std::string inp_str){
      str = inp_str;
      tknzr tokenize(str);
      
      tknzr_err = tokenize.tokenize_formula(toks);
      //std::cout<<"hi I am here 2"<<tknzr_err<<std::endl;
      if (tknzr_err){
      //std::cout<<"hi I am here 3"<<std::endl;
      //tokenize.print_tokens(toks);
      tok_end = &(toks.back());
      tok_ptr = &(toks.front());}
}
parser_tree parse_term();
parser_tree parse_conjterm();
parser_tree check_formula();
parser_tree check_parser();
bool check_end();
};
#endif