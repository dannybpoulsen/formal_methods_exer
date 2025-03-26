#include "components/compiler.hpp"
#include <unordered_map>

namespace components {
  struct Compiler::Internal {
    IR::CFA cfa;
    IR::Location_ptr start;
    IR::Location_ptr end;
    IR::Expr_ptr expr;
    std::unordered_map<std::string,IR::Register_ptr> vars;
  };
    
    IR::CFA Compiler::Compile (const Whiley::Program& prgm) {
      Internal mystore;
      _internal = &mystore;

      for (auto& var : prgm.getVars ()) {
	mystore.vars.emplace (var.getName(),mystore.cfa.makeRegister (var.getName()));
      }

      mystore.start = mystore.cfa.makeLocation ("Init",true);
      
      prgm.getStmt ().accept(*this);
      
      return mystore.cfa;
    }
      
    
    void Compiler::visitIdentifier (const Identifier& ids) {
      _internal->expr = _internal->vars.at(ids.getName ());
    }
    
    void Compiler::visitNumberExpression (const NumberExpression& num) {
      _internal->expr = std::make_shared<IR::Constant> (num.getValue ());
    }

    void Compiler::visitDerefExpression (const DerefExpression& num) {
      num.getMem ().accept (*this);
      _internal->expr = std::make_shared<IR::DerefExpr> (_internal->expr);
    }

    void Compiler::visitCastExpression (const CastExpression& num) {
      num.getExpression ().accept (*this);
      //_internal->expr = std::make_shared<IR::DerefExpr> (_internal->expr);
    }
    
    void Compiler::visitBinaryExpression (const BinaryExpression& be) {
      be.getLeft ().accept (*this);
      auto le = _internal->expr;
      be.getRight ().accept (*this);
      auto right = _internal->expr;
      bool _signed = be.getLeft().getType () == Whiley::Type::SI8;
      switch (be.getOp ()) {
	case BinOps::Add:
	  _internal->expr = std::make_shared<IR::AddExpr> (std::move(le),std::move(right));
	  break;
      case BinOps::Sub:
	_internal->expr = std::make_shared<IR::SubExpr> (std::move(le),std::move(right));
	break;
      case BinOps::Mul:
	_internal->expr = std::make_shared<IR::MulExpr> (std::move(le),std::move(right));
	break;
      case BinOps::Div:
	if (_signed) {
	  _internal->expr = std::make_shared<IR::SDivExpr> (std::move(le),std::move(right));
	}
	else
	  _internal->expr = std::make_shared<IR::DivExpr> (std::move(le),std::move(right));
	break;
      case BinOps::LEq:
	if (_signed)
	  _internal->expr = std::make_shared<IR::SLEqExpr> (std::move(le),std::move(right));
	else
	  _internal->expr = std::make_shared<IR::LEqExpr> (std::move(le),std::move(right));
	break;
      case BinOps::GEq:
	if (_signed)
	  _internal->expr = std::make_shared<IR::SGEqExpr> (std::move(le),std::move(right));
	else 
	  _internal->expr = std::make_shared<IR::GEqExpr> (std::move(le),std::move(right));
	break;
      case BinOps::Lt:
	if (_signed)
	  _internal->expr = std::make_shared<IR::SLtExpr> (std::move(le),std::move(right));
	else
	  _internal->expr = std::make_shared<IR::LtExpr> (std::move(le),std::move(right));
	break;
      case BinOps::Gt:
	if (_signed)
	  _internal->expr = std::make_shared<IR::SGtExpr> (std::move(le),std::move(right));
	else
	  _internal->expr = std::make_shared<IR::GtExpr> (std::move(le),std::move(right));
	
	break;
      case BinOps::Eq:
	_internal->expr = std::make_shared<IR::EqExpr> (std::move(le),std::move(right));
	break;
      case BinOps::NEq:
	_internal->expr = std::make_shared<IR::NEqExpr> (std::move(le),std::move(right));
	break;
	
	
      };
    }
    
    void Compiler::visitAssignStatement (const AssignStatement& ass) {
      auto reg = _internal->vars.at (ass.getAssignName ());
      ass.getExpression ().accept(*this);
      //_internal->start->setName (static_cast<std::string> (ass.getFileLocation ()));
      auto end = _internal->cfa.makeLocation ("",false);
      _internal->start->addEdge (std::make_shared<IR::Assign> (reg,_internal->expr),end);
      _internal->end = end;
    }

    void Compiler::visitAssertStatement (const AssertStatement& ass) {
      
      ass.getExpression ().accept(*this);
      auto expr = _internal->expr;
      auto nexpr = std::make_shared<IR::NegationExpr> (expr);
      auto assert_violated = _internal->cfa.makeLocation ("AssertViolation",false,true);
      //_internal->start->setName (static_cast<std::string> (ass.getFileLocation ()));
      _internal->start->addEdge (std::make_shared<IR::Assume> (nexpr),assert_violated);
      
      // continuation
      auto nloc = _internal->cfa.makeLocation ("",false);
      _internal->start->addEdge (std::make_shared<IR::Assume> (expr),nloc);
      _internal->end = nloc;
    }

    void Compiler::visitAssumeStatement (const AssumeStatement& ass) {
      
      ass.getExpression ().accept(*this);
      auto expr = _internal->expr;
      
      // continuation
      auto nloc = _internal->cfa.makeLocation ("",false);
      //_internal->start->setName (static_cast<std::string> (ass.getFileLocation ()));
      _internal->start->addEdge (std::make_shared<IR::Assume> (expr),nloc);
      _internal->end = nloc;
    }
    
    void Compiler::visitNonDetAssignStatement (const NonDetAssignStatement& ass) {
      auto reg = _internal->vars.at (ass.getAssignName ());
      auto end = _internal->cfa.makeLocation ("",false);
      //_internal->start->setName (static_cast<std::string> (ass.getFileLocation ()));
      
      _internal->start->addEdge (std::make_shared<IR::Assign> (reg,std::make_shared<IR::Undef> ()),end);
      _internal->end = end;
    }
    
    void Compiler::visitIfStatement (const IfStatement& ifs ) {
      ifs.getCondition ().accept(*this);
      auto posExpr = _internal->expr;
      auto negExpr = std::make_shared<IR::NegationExpr> (_internal->expr);
      auto my_start = _internal->start;
      //_internal->start->setName (static_cast<std::string> (ifs.getFileLocation ()));
      auto my_end = _internal->cfa.makeLocation ("",false);
      
      //IfBody
      {
	auto nloc = _internal->cfa.makeLocation ("",false);
	my_start->addEdge (std::make_shared<IR::Assume> (posExpr),nloc);
	_internal->start = nloc;
	ifs.getIfBody ().accept(*this);
	_internal->end->addEdge (std::make_shared<IR::Skip> (),my_end);
	
      }

      //else body
      {
	auto nloc = _internal->cfa.makeLocation ("",false);
	my_start->addEdge (std::make_shared<IR::Assume> (negExpr),nloc);
	_internal->start = nloc;
	ifs.getElseBody ().accept(*this);
	_internal->end->addEdge (std::make_shared<IR::Skip> (),my_end);
	
      }

      
      // Construct start edge for
      

      _internal->end = my_end;
    }
    void Compiler::visitSkipStatement (const SkipStatement& ass) {
      auto end = _internal->cfa.makeLocation ("",false);
      //_internal->start->setName (static_cast<std::string> (ass.getFileLocation ()));
      _internal->start->addEdge (std::make_shared<IR::Skip> (),end);
      _internal->end = end;
      
    }

    void Compiler::visitWhileStatement (const WhileStatement& whiles) {
      whiles.getCondition ().accept(*this);
      auto posExpr = _internal->expr;
      auto negExpr = std::make_shared<IR::NegationExpr> (_internal->expr);
      //_internal->start->setName (static_cast<std::string> (whiles.getFileLocation ()));
      auto my_start = _internal->start;
      auto my_end = _internal->cfa.makeLocation ("",false);
      auto body =  _internal->cfa.makeLocation ("",false);
      
      _internal->start->addEdge (std::make_shared<IR::Assume> (negExpr),my_end);
      _internal->start->addEdge (std::make_shared<IR::Assume> (posExpr),body);
      _internal->start = body;
      whiles.getBody ().accept(*this);
      _internal->end->addEdge (std::make_shared<IR::Skip> (),my_start);
      
      _internal->end = my_end;
    }

    
    void Compiler::visitMemAssignStatement (const MemAssignStatement& assign) {
        assign.getMemLoc ().accept (*this);
	auto mem = _internal->expr;
	assign.getExpression ().accept (*this);
	auto assigne = _internal->expr;
	auto my_end = _internal->cfa.makeLocation ("",false);
	
	_internal->start->addEdge (std::make_shared<IR::Store> (assigne,mem),my_end);
	_internal->end = my_end;
	
      }
      
    
    void Compiler::visitSequenceStatement (const SequenceStatement&  s) {
      s.getFirst().accept (*this);
      _internal->start = _internal->end;
      s.getSecond().accept (*this);
      
    }
      
    
  }
