#include "satSolver.h"
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include <memory>
#include <map>
bool satCallingMiniSat(std::vector<std::vector<int>> &cnf) {
  // your code starts here
  std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
  std::map<int, Minisat::Lit> LIT_ID_TABLE;
  for (long unsigned int i = 0; i < cnf.size(); i++) {
    Minisat::vec<Minisat::Lit> CLAUSE;
    for (long unsigned int j = 0; j < cnf[i].size(); j++) {
      if(LIT_ID_TABLE.find(abs(cnf[i][j])) == LIT_ID_TABLE.end()) {
        Minisat::Lit l1  = Minisat::mkLit(solver->newVar());
        LIT_ID_TABLE[abs(cnf[i][j])] = l1;
      }
      if(cnf[i][j]<0){
        CLAUSE.push(~LIT_ID_TABLE[abs(cnf[i][j])]);
      }
      else{
        CLAUSE.push(LIT_ID_TABLE[abs(cnf[i][j])]);
      }
    }
    solver->addClause (CLAUSE);
  }
  return solver->solve();
}
