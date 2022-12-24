#include <string>
#include <vector>
#include <map>
#include "dpll.h"
#include <iostream>
std::string DPLL::solve(){
    std::sort(F.begin(), F.end(), []
    (const std::vector<int>& first, const std::vector<int>& second){
        return first.size() < second.size();
    });
    std::string ret = "unsat";
    if (DPLL::sat()){
        ret = "sat";
        return ret;
    }
    else{
        return ret;
    }
}

bool DPLL::sat(){
    //std::cout<<"++++++++++++++++++++++++++++"<<std::endl;
    //print_F();
    if (A.size() == 0){
        PLP();
    }
    else{
        bcp();
        PLP();
    }
    //std::cout<<"Size of F "<<F.size()<<" Line number "<<__LINE__<<std::endl;
    if (F.size() == 0) {
        return true;
    }
    if (check_empty_clause()){
        //std::cout<<"returning false"<<" Line number "<<__LINE__<<std::endl;
        return false;
    }
    int p = choose_var_not_in_A();
    //std::cout<<"Chose P "<<p<<" Line number "<<__LINE__<<std::endl;
    std::map<int,bool> temp = A;
    std::vector<std::vector<int>> temp_F = F;
    A[abs(p)] = true;
    if (sat()){
        return true;
    }
    else{
        A = temp;
        F = temp_F;
        A[abs(p)] = false;
        return sat();
    }
}

void DPLL::PLP(){
    //std::cout<<"Inside PLP"<<" Line number "<<__LINE__<<std::endl;
    std::vector<int> L;
    for(int i =1; i<=Var_count; i++){
        if(check_if_pos(i)){
            A[abs(i)] = true;
            L.push_back(i);
        }
        if(check_if_neg(i)){
            A[abs(i)] = false;
            L.push_back(i);
        }
    }
    if (L.size() == 0){
        //std::cout<<"There is no PLP"<<" Line number "<<__LINE__<<std::endl;
        return;
    }
    //std::vector<int> rem_clause;
    for (int i = 0; i < L.size(); i++){
        std::vector<std::vector<int>>::iterator iter = F.begin();
        for(iter; iter<F.end(); iter++){
            std::vector<int> clause = *iter;
            std::vector<int>::iterator iter_c = clause.begin();
            for(iter_c; iter_c<clause.end(); iter_c++){
                int literal = *iter_c;
                int unsigned_literal = abs(literal);
                if(unsigned_literal == L[i]){
                    F.erase(iter);
                    iter--;
                    break;
                }
            }
        }
    }
    
    //print_F();
    return;
}

void DPLL::bcp(){
    //std::cout<<"Inside BCP"<<std::endl;
    int prev_count = A.size();
    while(F.size()>0 || A.size() == Var_count){
        std::vector<std::vector<int>>::iterator iter = F.begin();
        for(iter; iter<F.end(); iter++){
            //std::cout<<__LINE__<<std::endl;
            std::vector<int> clause = *iter;
            std::vector<int>::iterator iter_c = (*iter).begin();
            bool flag = false;
            for(iter_c; iter_c<(*iter).end(); iter_c++){
                
                int literal = *iter_c;
                int unsigned_literal = abs(literal);
                //std::cout<<literal<<" "<<__LINE__<<std::endl;
                if(A.find(unsigned_literal) == A.end()){
                    //std::cout<<__LINE__<<std::endl;
                    continue;
                }
                /*
                if((*iter).size() == 1){
                    continue;
                }*/
                if(((A[unsigned_literal])&&(literal > 0))||((!A[unsigned_literal])&&(literal<0))){
                    //std::cout<<__LINE__<<std::endl;
                    //std::cout<<"Removing clauses with "<<literal<<std::endl;
                    //print_F();
                    F.erase(iter);
                    //print_F();
                    iter--;
                    flag = true;
                    break;
                }
                if(((A[unsigned_literal])&&(literal < 0))||((!A[unsigned_literal])&&(literal>0))){
                    //std::cout<<__LINE__<<std::endl;
                    //std::cout<<"Erasing"<<(*iter_c)<<std::endl;
                    //print_F();
                    (*iter).erase(iter_c);
                    //print_F();
                    if((*iter).size()!=0){
                        iter_c--;
                    }
                    else{
                        break;
                    }
                    continue;
                }
            }
            if (flag){
                continue;
            }
            if ((*iter).size() == 1){
                //std::cout<<__LINE__<<std::endl;
                int literal = (*iter)[0];
                int unsigned_literal = abs(literal); 
                if(A.find(unsigned_literal)==A.end()){
                    if (literal>0){
                        A[unsigned_literal] = true;
                    }
                    else{
                        A[unsigned_literal] = false;
                    }
                }
                //print_F();
                F.erase(iter);
                //print_F();
                iter--;
            }
        }
        if (prev_count == A.size()){
            return;
        }
        prev_count = A.size();
    }
    return;
}

void DPLL::remove_element(std::vector<int> rem, std::vector<int>& vec){
    sort(rem.begin(), rem.end());
    rem.erase( unique( rem.begin(), rem.end() ), rem.end() );
    int counter = 0;
    for (int j = 0; j<rem.size();j++){
        vec.erase(vec.begin() + rem[j]+counter);
        counter-=1;
    }
    return;
}




bool DPLL::check_empty_clause(){
    for (int j = 0; j<F.size();j++){
        if (F[j].size() == 0){
            //std::cout<<"UNNSAT"<<std::endl;
            return true;
        }
    }
    return false;
}

bool DPLL::check_if_pos(int i){
    //std::cout<<"checking positivity of "<<i<<" Line number "<<__LINE__<<std::endl;
    bool ret = true;
    for (int i = 0; i<F.size();i++){
        for (int j = 0; j<F.size();j++){
            if (j*-1 == i){
                ret = false;
                return ret;
            }
        }
    }
    return ret;
}

bool DPLL::check_if_neg(int i){
    //std::cout<<"checking negativity of "<<i<<" Line number "<<__LINE__<<std::endl;
    bool ret = true;
    for (int i = 0; i<F.size();i++){
        for (int j = 0; j<F.size();j++){
            if (j == i){
                ret = false;
                return ret;
            }
        }
    }
    return ret;
}
void DPLL::remove_clause(std::vector<int> rem){
    //std::cout<<"Removing  The clause size of F"<<F.size()<<" Line number "<<__LINE__<<std::endl;
    //std::cout<<"No. of clauses to be removed"<<rem.size()<<" Line number "<<__LINE__<<std::endl;
    //std::vector<std::vector<int>> new_F;
    sort(rem.begin(), rem.end());
    rem.erase( unique( rem.begin(), rem.end() ), rem.end() );
    int counter = 0;
    for (int j = 0; j<rem.size();j++){
        F.erase(F.begin()+rem[j]+counter);
        counter -= 1;
        //std::cout<<"Removing  The clause number"<<rem[j]<<" Line number "<<__LINE__<<std::endl;
        //std::cout<<"Removing  The clause size of F"<<F.size()<<" Line number "<<__LINE__<<std::endl;
    }
    //std::cout<<"Removed  The clause size of F"<<F.size()<<" Line number "<<__LINE__<<std::endl;  
    return;
}

void DPLL::print_F(){
    std::cout<<"[";
    for (int i = 0; i < F.size(); i++){
        std::cout<<"[";
        for (int j = 0; j < F[i].size(); j++) {
            if (j==F[i].size()-1){
                std::cout<<F[i][j]<<"]";
                continue;
            }
            std::cout<<F[i][j]<<",";
        }
    }
    std::cout<<"]"<<std::endl;
}

int DPLL::choose_var_not_in_A(){
    for(int i = 1; i<=Var_count; i++){
        if(A.find(i)==A.end()){
            return i;
        }
    }
    return 0;
}

void DPLL::print_assignment(){
    std::map<int, bool>::iterator it;
    std::cout<<"{";
    for (it = A.begin(); it != A.end(); it++){
        std::cout<<it->first<<":"<<it->second<<",";
    }
    std::cout<<"} line number"<<__LINE__<<std::endl;
} 