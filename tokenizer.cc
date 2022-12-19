#include "tokenizer.h"


bool tknzr::tokenize_formula(std::vector<token> &f_toks){
  char *ptr = &str[0];
  bool check_var, space; 
  if(*ptr=='\0'){
    //std::cout<<"- - - - - "<<std::endl;
    return false;  
  }
  while(*ptr!='\0'){
    //std::cout<<"++++++"<<*ptr<<std::endl;
    token tok;
    check_var = false;
    space = false;
    switch(*ptr){
      case '0':
          tok.Type = "Value";
          tok.Content = "0";
          ptr++;
          break;
      case '1':
          tok.Type = "Value";
          tok.Content = "1";
          ptr++;
          break;
      case '+':
          tok.Type = "OPERATOR";
          tok.Content = "+";
          ptr++;
          break;
      case '-':
          tok.Type = "OPERATOR";
          tok.Content = "-";
          ptr++;
          break;
      case '*':
          tok.Type = "OPERATOR";
          tok.Content = "*";
          ptr++;
          break;
      case '(':
          tok.Type = "OPEN";
          tok.Content = "(";
          ptr++;
          break;
      case ')':
          tok.Type = "CLOSE";
          tok.Content = ")";
          ptr++;
          break;
      case ' ':
          space = true;
          ptr++;
          break;
      default:
          check_var = true;}

        if (check_var){
          if((int(*ptr)>=int('a')&&int(*ptr)<=('z'))||(int(*ptr)>=int('A')&&int(*ptr)<=('Z'))){
            std::string s;
            int i=0;
            while((*ptr!='(') && (*ptr!=')') && (*ptr!='+') && (*ptr!='-') && (*ptr!='*') && (*ptr!='\0')&&(((int(*ptr)>=int('a')&&int(*ptr)<=('z'))||(int(*ptr)>=int('A')&&int(*ptr)<=('Z'))) || ((int(*ptr)>=int('0')&&int(*ptr)<=('9'))))){
              //std::cout<<"---"<<*ptr<<"---"<<std::endl;
              if (i>=10){
                return false;
              }
              if(*ptr==' '){
                return false;
              }
                s+=*ptr;
                ++ptr;
                ++i;
            }
            tok.Type = "Var";
            tok.Content = s;
          }
          else{
            return false;
          }

        }
        if (space){
          continue;
        }
        
      f_toks.push_back(tok);
      if(*ptr=='\0'){
        //std::cout<<"hi I am here 1"<<std::endl;
          
        }
      }token new_tok;
          new_tok.Content="NA";
          new_tok.Type="end";
          new_tok.last=true;
          f_toks.push_back(new_tok);
          return true;}

void tknzr::print_tokens(std::vector<token> &f_toks){
  //std::cout<<"The tokenized vector is: "<<std::endl;
  for (auto i = f_toks.begin();i!=f_toks.end();i++){
   //std::cout<<(*i).Content<<" "<<(*i).Type<<std::endl;
  }

}
