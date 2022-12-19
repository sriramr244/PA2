#include "Tseitin_transform.h"
#include <vector>
#include<iostream>

TseitinTransformer::TseitinTransformer(TreeNode *formulaRoot): root{formulaRoot} {}

int TseitinTransformer::transSubformula(TreeNode* root) {
  std::string content = root->getContent();
  if ((content == "+")||(content=="*")){
    int curID = varIdCounter++;
    std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
    int leftID = 0;
    int rightID = 0;
    if((root->getLeftChild()->getContent() != "+") && (root->getLeftChild()->getContent() != "*") &&
        (root->getLeftChild()->getContent() != "-")){
        if(!(varIdTable.count(root->getLeftChild()->getContent())>0)){
          leftID = varIdCounter++;
          std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
          varIdTable.insert(std::pair<std::string, int>(root->getLeftChild()->getContent(), leftID));
        }
        else{
          leftID = varIdTable[root->getLeftChild()->getContent()];
        }
    }
    else{
      leftID = varIdCounter;
      //std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
      transSubformula(root->getLeftChild());
    }
    if((root->getRightChild()->getContent() != "+") && (root->getRightChild()->getContent() != "*") &&
        (root->getRightChild()->getContent() != "-")){
        if(!(varIdTable.count(root->getRightChild()->getContent())>0)){
          rightID = varIdCounter++;
          std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
          varIdTable.insert(std::pair<std::string, int>(root->getRightChild()->getContent(), rightID));
        }
        else{
          rightID = varIdTable[root->getRightChild()->getContent()]; 
        }
    }
    else{
      rightID = varIdCounter;
      //std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
      transSubformula(root->getRightChild());
    }
    if (content =="+"){
      std::cout<<curID<<leftID<<rightID<<std::endl;
      addOrEq(curID, leftID, rightID);
    }
    else{
      std::cout<<curID<<leftID<<rightID<<std::endl;
      addAndEq(curID, leftID, rightID);
    }
    return 0;
  }
  else if (content == "-"){
    std::cout<<"INSIDE NEG"<<std::endl;
    int curID = varIdCounter++;
    std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
    int leftID = 0;
    if((root->getLeftChild()->getContent() != "+") && (root->getLeftChild()->getContent() != "*") &&
        (root->getLeftChild()->getContent() != "-")){
        if(!(varIdTable.count(root->getLeftChild()->getContent())>0)){
          leftID = varIdCounter++;
          std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
          varIdTable.insert(std::pair<std::string, int>(root->getLeftChild()->getContent(), leftID));
        }
        else{
          leftID = varIdTable[root->getLeftChild()->getContent()];
        }
    }
    else{
      leftID = varIdCounter;
      //std::cout<<"INCREMENTING"<<__LINE__<<":"<<varIdCounter<<std::endl;
      std::cout<<"calling REcursively"<<std::endl;
      transSubformula(root->getLeftChild());
    }
    addNegEq(curID, leftID);
    return 0;
  }
  else{
    return 1;
  }
}

void TseitinTransformer::addNegEq(int curID, int childID) {
  std::vector<int> vec1, vec2;
  vec1.push_back(curID*-1);
  vec1.push_back(childID*-1);
  vec2.push_back(curID);
  vec2.push_back(childID);
  cnf.push_back(vec1);
  cnf.push_back(vec2);
  return;
}

void TseitinTransformer::addOrEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> vec1, vec2, vec3;
  vec1.push_back(curID*-1);
  vec1.push_back(leftID);
  vec1.push_back(rightID);
  cnf.push_back(vec1);
  vec2.push_back(leftID*-1);
  vec2.push_back(curID);
  cnf.push_back(vec2);
  vec3.push_back(rightID*-1);
  vec3.push_back(curID);
  cnf.push_back(vec3);
  return;
}

void TseitinTransformer::addAndEq(int curID, int leftID, int rightID) {
  // your code starts here
  std::vector<int> vec1, vec2, vec3;
  vec2.push_back(curID*-1);
  vec2.push_back(leftID);
  cnf.push_back(vec2);
  vec3.push_back(curID*-1);
  vec3.push_back(rightID);
  cnf.push_back(vec3);
  vec1.push_back(leftID*-1);
  vec1.push_back(rightID*-1);
  vec1.push_back(curID);
  cnf.push_back(vec1);
}
std::vector<std::vector<int>> TseitinTransformer::transform() {
  transSubformula(root);
  std::vector<int> vec;
  vec.push_back(1);
  cnf.push_back(vec);
  return cnf;
}

std::string TseitinTransformer::cnfString() const {
  std::string result = "";
  // your code starts here
  return result;
}

unsigned int TseitinTransformer::getVarNum() const {
  // your code starts here
  return 0;
}
