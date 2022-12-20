#include <iostream>
#include <string>
#include <map>
#include "parser.h"
#include "tokenizer.h"
#include "treeNode.h"
#include <algorithm>
#include <vector>
#include "Tree_to_nnf.h"
#include "Tseitin_transform.h"
#include "satSolver.h"

bool formula();
bool conjterm();
using namespace std;
#define COUNT 10

void print2DUtil(TreeNode* root, int space=0)
{
    if (root == NULL){
        return;
	}
    space += COUNT;
    print2DUtil((*root).getRightChild(), space);
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << (*root).getContent() << "\n";
    print2DUtil((*root).getLeftChild(), space);
}


void parseLine(const std::string &line, std::string &formulaStr) {
  formulaStr = line;
  if(formulaStr==""){
    std::cout<<"Error: invalid input"<<std::endl;
    return;
  }
  else{
    formula_parser parse_form(formulaStr);
    if(!parse_form.tknzr_err){
      std::cout<<"Error: invalid input"<<std::endl;
      return;
    }
    parser_tree out = parse_form.check_parser();
    //cout<<out.error<<endl;
    if(out.error){
      //print2DUtil(out.tree_ptr, 0);
      /*try{
        cout<<(*(out.tree_ptr)).evaluate(parse_form.as_toks)<<endl;
      }
      catch(bool m){
        cout<<"Error: invalid assignment"<<endl;
      }*/
    }
    else{
      std::cout<<"Error: invalid input"<<std::endl;
    }
    /*TreeNode* nnf_out = cvt_nnf(out.tree_ptr);
    cout<<"NNF Tree: "<<endl;
    print2DUtil(nnf_out, 0);*/
    TseitinTransformer transfer_TS(out.tree_ptr);
    std::vector<std::vector<int>> cnf = transfer_TS.transform();
    /*for (int i = 0; i < cnf.size(); i++){
      std::cout<<"new"<<std::endl;
      for (int j = 0; j < cnf[i].size(); j++) {
        std::cout << cnf[i][j] << std::endl;
      }
    }*/
    bool SAT = satCallingMiniSat(cnf);
    if(SAT){
      std::cout<<"sat"<<std::endl;
    }
    else{
      std::cout<<"unsat"<<std::endl;
    }
    
    return;
  }
}

// The program shall continuously ask for new inputs from standard input and output to the standard output
// The program should terminate gracefully (and quietly) once it sees EOF
int main() {
    std::string line;
  while (true) // continuously asking for new inputs from standard input
  {
     // store each input line
    if(!cin.eof()){
    getline(cin,line);
    std::string formulaStr; // store the formula string
    std::string assignmentStr; // store the assignment string
    // your code starts here
      
      
      //cout<<line<<endl;
      //line = "1";
      //line = "A + B * -0 * (1 + -CD)";
      
    //line = "A + B * -0 * (1 + -CD); A : 1, B : 0, CD : 1";
      //line.erase(remove_if(line.begin(), line.end(),::isspace), line.end());
      if (line!=""){
      //cout<<line<<endl;
      
      parseLine(line, formulaStr);}
      else if(!cin.eof()){
        cout<<"Error: invalid input"<<__LINE__<<endl;
      }}
      else{
        break;
      }
//cout<<formulaStr;
      //break;
      
  }
    return 1;
}


