#include "parser.h"



bool formula_parser::check_end(){
    //std::cout<<"Inside checking the end of vector "<<(*tok_ptr).last<<":"<<(*tok_ptr).Content<<" "<<tok_end<<" "<<tok_ptr<<std::endl;
if ((*tok_ptr).last){
        return true;
    }
return false;
}
parser_tree formula_parser::check_parser(){
    if (!formula_parser::tknzr_err){
        parser_tree out;
        out.tree_ptr = nullptr;
        out.error = false;
        return out;
    }
    //std::cout<<"Inside the parser "<<(*tok_ptr).Content<<std::endl;

    parser_tree b = formula_parser::check_formula();
    if (!formula_parser::check_end()){
        parser_tree out;
        out.tree_ptr = nullptr;
        out.error = false;
        return out;
    }
    return b;
}


parser_tree formula_parser::check_formula(){
    //std::cout<<"Inside the formula checker "<<(*tok_ptr).Content<<std::endl;
    parser_tree cct = formula_parser::parse_conjterm();
    bool end = formula_parser::check_end();
    //std::cout<<"cct "<<cct.error<<(*tok_ptr).Content<<std::endl;
    if (!end&&cct.error){
    //std::cout<<"checking the + sign"<<(*tok_ptr).Content<<std::endl;
    if(cct.error&&((*tok_ptr).Content == "+")){
        TreeNode* new_ptr = new OperatorNode("+");
        //new_ptr->leftChild = cct.tree_ptr;
        (*new_ptr).updateLeftChild(cct.tree_ptr);
        ++tok_ptr;
        cct = formula_parser::check_formula();
        parser_tree cft;
        //new_ptr->rightChild = cct.tree_ptr;
        (*new_ptr).updateRightChild(cct.tree_ptr);
        cft.tree_ptr = new_ptr;
        cft.error = cct.error;
        return cft;
    }
    else{
        //std::cout<<"Not the + "<<(*tok_ptr).Content<<std::endl;
        return cct;
    }}
    else{
        //std::cout<<"Reached the end of the string"<<(*tok_ptr).Content<<std::endl;
        return cct;
    }
}


parser_tree formula_parser::parse_conjterm(){
    //std::cout<<"Inside the conjterm checker "<<(*tok_ptr).Content<<std::endl;
    parser_tree ct = formula_parser::parse_term();
    bool end = formula_parser::check_end();
    //std::cout<<"ct "<<ct.error<<(*tok_ptr).Content<<std::endl;
    if(!end &&ct.error){
        //std::cout<<"checking the * sign "<<(*tok_ptr).Content<<std::endl;
        if ((*tok_ptr).Content=="*"){
            //std::cout<<"Inside the * checker "<<(*tok_ptr).Content<<std::endl;
            TreeNode* new_ptr = new OperatorNode("*");
            //new_ptr->leftChild = ct.tree_ptr;
            (*new_ptr).updateLeftChild(ct.tree_ptr);
            ++tok_ptr;
            ct = formula_parser::parse_conjterm();
            parser_tree ct1;
            //new_ptr->rightChild = ct.tree_ptr;
            (*new_ptr).updateRightChild(ct.tree_ptr);
            ct1.tree_ptr = new_ptr;
            ct1.error = ct.error;
            return ct1;
        }
        else{
            //std::cout<<"Not the * "<<(*tok_ptr).Content<<std::endl;
            return ct;
        }
    }
    else{
        return ct;
    }
}

parser_tree formula_parser::parse_term(){
    parser_tree return_var;
    return_var.error = false;
    return_var.tree_ptr = nullptr;
        //std::cout<<"Inside the term checker "<<(*tok_ptr).Content<<std::endl;
        if((*tok_ptr).Type=="Value"){
            //std::cout<<"Inside the value checker "<<(*tok_ptr).Content<<std::endl;
            
            TreeNode* new_node = new ConstantNode((*tok_ptr).Content);
            return_var.tree_ptr = new_node;
            return_var.error = true;
            ++tok_ptr;
            return return_var;}
        
        if((*tok_ptr).Type=="Var"){
            //std::cout<<"Inside the Var checker "<<(*tok_ptr).Content<<std::endl;
            
            TreeNode* new_node = new VariableNode((*tok_ptr).Content);
            return_var.tree_ptr = new_node;
            return_var.error = true;
            ++tok_ptr;
            return return_var;}


        if((*tok_ptr).Content=="-"){
                //std::cout<<"Inside the - checker "<<(*tok_ptr).Content<<std::endl;
                TreeNode* new_node = new OperatorNode((*tok_ptr).Content);
                ++tok_ptr;
                parser_tree nega_parser = formula_parser::parse_term();
                return_var.error = nega_parser.error;
                //new_node->leftChild = nega_parser.tree_ptr;
                (*new_node).updateLeftChild(nega_parser.tree_ptr);
                return_var.tree_ptr = new_node;
                return return_var;
            }

        if ((*tok_ptr).Type=="OPEN"){
            //std::cout<<"Inside the ( checker "<<(*tok_ptr).Content<<std::endl;
            ++tok_ptr;
            parser_tree final_var;
            final_var.error = false;
            final_var.tree_ptr = nullptr;
            parser_tree intr_var = formula_parser::check_formula();
            bool end = formula_parser::check_end();
            if(intr_var.error && !end){
                if((*tok_ptr).Content==")"){
                    //std::cout<<"Inside the ) checker "<<(*tok_ptr).Content<<std::endl;
                    ++tok_ptr;
                    final_var.error = intr_var.error;
                    final_var.tree_ptr = intr_var.tree_ptr;
                }}
            return_var = final_var;
            return return_var;
            }
    return return_var;
}