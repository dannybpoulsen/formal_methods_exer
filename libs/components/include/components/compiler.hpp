
#include "ir/cfa.hpp"
#include "whiley/ast.hpp"

namespace components {
  using namespace Whiley;
  
  class Compiler : private NodeVisitor {
  public:
    IR::CFA Compile (const Whiley::Program&);
    void visitIdentifier (const Identifier&) override ;
    void visitNumberExpression (const NumberExpression& ) override ; 
    void visitDerefExpression (const DerefExpression& ) override ;
    void visitBinaryExpression (const BinaryExpression& ) override ;  
    void visitAssignStatement (const AssignStatement& ) override ; 
    void visitAssertStatement (const AssertStatement& ) override ; 
    void visitAssumeStatement (const AssumeStatement& ) override ; 
    void visitNonDetAssignStatement (const NonDetAssignStatement& ) override ; 
    
    void visitIfStatement (const IfStatement& ) override ; 
    void visitSkipStatement (const SkipStatement& ) override ; 
    void visitWhileStatement (const WhileStatement& ) override ; 
    void visitSequenceStatement (const SequenceStatement& ) override ; 
    void visitMemAssignStatement (const MemAssignStatement&) override;
    void visitCastExpression (const CastExpression& ) override;
      
  private:
    struct Internal;
    Internal* _internal = nullptr;
  };
  
  
}
