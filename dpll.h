#ifndef DPLL_H
#define DPLL_H
#include <string>
#include <vector>
#include <unordered_map>

class DPLL{
    private:
        std::vector<std::vector<int>> F;
        std::map<int,bool> A;
        int Var_count;
        void bcp();
        void PLP();
        bool check_empty_clause();
        int choose_var();
        bool sat();
        void remove_clause(std::vector<int> rem);
        bool check_if_pos(int i);
        bool check_if_neg(int i);
        void remove_element(std::vector<int> rem, std::vector<int>& vec);
        void print_F();
        int choose_var_not_in_A();
        void print_assignment();

    public:
        std::string solve();
        DPLL(std::vector<std::vector<int>> cnf, int count){
            F = cnf;
            Var_count = count;
        }
        
};

#endif

