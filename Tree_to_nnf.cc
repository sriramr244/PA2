#include "Tree_to_nnf.h"
#include <iostream>
#include <string>
#include "treeNode.h"


TreeNode* cvt_nnf(TreeNode* root){
  std::string content = root->getContent();
  if ((content == "*")||(content =="+")){
    root->updateLeftChild(cvt_nnf(root->getLeftChild()));
    root->updateRightChild(cvt_nnf(root->getRightChild()));
  }
  else if(content == "-"){
    root = push_neg(root->getLeftChild());
  }
  return root;
}

TreeNode* push_neg(TreeNode* node){
  std::string content = node->getContent();
  if((content == "*")||(content == "+")){
    TreeNode* new_ptr1 = new OperatorNode("-");
    TreeNode* new_ptr2 = new OperatorNode("-");
    new_ptr1->updateLeftChild(node->getLeftChild());
    new_ptr2->updateLeftChild(node->getRightChild());
    std::string op;
    if (content=="*"){
      op = "+";
    }
    else{
      op = "*";
    }
    TreeNode* ret_node = new OperatorNode(op);
    ret_node->updateLeftChild(cvt_nnf(new_ptr1));
    ret_node->updateRightChild(cvt_nnf(new_ptr2));
    return ret_node;
  }
  else if(content == "-"){
    return cvt_nnf(node->getLeftChild());
  }
  else{
    TreeNode* new_ptr = new OperatorNode("-");
    new_ptr->updateLeftChild(node);
    return new_ptr;
  }
}