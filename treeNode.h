#ifndef TNODE_H
#define TNODE_H

#include <string>
#include <map>

// abstract superclass of the syntax tree node
class TreeNode {
    std::string content;
    TreeNode *leftChild = nullptr;
    TreeNode *rightChild = nullptr;
  public:
    TreeNode *getLeftChild() const;
    TreeNode *getRightChild() const;
    TreeNode(std::string cntt);
    std::string getContent() const;
    virtual bool evaluate(std::map<std::string,bool>&assign_toks) const = 0; // pure virtual method
    void updateLeftChild(TreeNode *lChild); // for the operator "-", the operand is stored in leftChild
    void updateRightChild(TreeNode *rChild);
    void updateContent(std::string cnt);
    virtual ~TreeNode();

};

// concrete tree node of opertaor type
class OperatorNode : public TreeNode {
  public:
    OperatorNode(std::string cntt);
    //bool evaluate(const std::map<std::string, bool> &assignment) const override;
    bool evaluate(std::map<std::string,bool>&assign_toks) const override;
};

// concrete tree node of constant type
class ConstantNode : public TreeNode {
  public:
    ConstantNode(std::string cntt);
    //bool evaluate(const std::map<std::string, bool> &assignment) const override;
    bool evaluate(std::map<std::string,bool>&assign_toks) const override;
};

// concrete tree node of varibale type
class VariableNode : public TreeNode {
  public:
    VariableNode(std::string cntt);
    bool evaluate(std::map<std::string,bool>&assign_toks) const override;
};

#endif
