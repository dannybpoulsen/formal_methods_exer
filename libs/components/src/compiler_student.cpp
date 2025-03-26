#include "components/compiler.hpp"
#include "components/notsolver.hpp"

#include <unordered_map>

namespace components {
struct Compiler::Internal {
  IR::CFA cfa;
  IR::Location_ptr start;
  IR::Location_ptr end;
  IR::Expr_ptr expr;
  std::unordered_map<std::string, IR::Register_ptr> vars;
};

IR::CFA Compiler::Compile(const Whiley::Program &prgm) {
  Internal mystore;
  _internal = &mystore;
  
  for (auto& var : prgm.getVars ()) {
    mystore.vars.emplace (var.getName(),mystore.cfa.makeRegister (var.getName()));
  }
  
  mystore.start = mystore.cfa.makeLocation ("Init",true);
  
  prgm.getStmt ().accept(*this);
  
  return mystore.cfa;
}

void Compiler::visitIdentifier(const Identifier &ids) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitNumberExpression(const NumberExpression &num) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitDerefExpression(const DerefExpression &num) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitCastExpression(const CastExpression &num) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitBinaryExpression(const BinaryExpression &be) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitAssignStatement(const AssignStatement &ass) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitAssertStatement(const AssertStatement &ass) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitAssumeStatement(const AssumeStatement &ass) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitNonDetAssignStatement(const NonDetAssignStatement &ass) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitIfStatement(const IfStatement &ifs) {
  throw NotSolvedYet{__FILE__};
}
void Compiler::visitSkipStatement(const SkipStatement &ass) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitWhileStatement(const WhileStatement &whiles) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitMemAssignStatement(const MemAssignStatement &assign) {
  throw NotSolvedYet{__FILE__};
}

void Compiler::visitSequenceStatement(const SequenceStatement &s) {
  throw NotSolvedYet{__FILE__};
}

} // namespace components
