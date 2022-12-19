#include "treeNode.h"
#include <iostream>
TreeNode::TreeNode(std::string cntt): content {cntt} {}

std::string TreeNode::getContent() const {
  return TreeNode::content;
}

TreeNode *TreeNode::getLeftChild() const {
  // your code starts here
  return TreeNode::leftChild;
}
TreeNode *TreeNode::getRightChild() const {
  // your code starts here
  return TreeNode::rightChild;
}

void TreeNode::updateLeftChild(TreeNode *lChild) {
  // your code starts here
  TreeNode::leftChild = lChild;
}

void TreeNode::updateRightChild(TreeNode *rChild) {
  // your code starts here
  TreeNode::rightChild = rChild;
}
void TreeNode::updateContent(std::string cnt) {
  // your code starts here
  TreeNode::content = cnt;
}

OperatorNode::OperatorNode(std::string cntt): TreeNode{cntt} {
}

bool OperatorNode::evaluate(std::map<std::string,bool> &assign_toks) const {
  // your code starts here
  if(TreeNode::getContent() == "*"){
    bool b1 = TreeNode::getLeftChild()->evaluate(assign_toks);
    bool b2 = TreeNode::getRightChild()->evaluate(assign_toks);
      return  b1 && b2;
  }
  if(TreeNode::getContent() == "+"){
    bool b1 = TreeNode::getLeftChild()->evaluate(assign_toks);
    bool b2 = TreeNode::getRightChild()->evaluate(assign_toks);
      return  b1 || b2;
  }

  if(TreeNode::getContent() == "-"){
    return !(TreeNode::getLeftChild()->evaluate(assign_toks));
  }

  return false;
}

ConstantNode::ConstantNode(std::string cntt): TreeNode{cntt} {}

bool ConstantNode::evaluate(std::map<std::string,bool>&assign_toks) const {
  // your code starts here
  if(TreeNode::getContent() == "1"){
      return true;
  }
  if(TreeNode::getContent() == "0"){
      return false;
  }

  return false;
}

VariableNode::VariableNode(std::string cntt): TreeNode{cntt} {}

bool VariableNode::evaluate(std::map<std::string,bool> &assign_toks) const {
  
  if (!(assign_toks.count(TreeNode::getContent())==1)){
    throw(true);
  }
  else{
    return assign_toks[TreeNode::getContent()];
  }
  
  
  return false;
}

TreeNode::~TreeNode() {
  // your code starts here
}
