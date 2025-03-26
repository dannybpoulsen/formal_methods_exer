#ifndef _STATE__
#define _STATE__

#include "ir/expr.hpp"
#include "ir/cfa.hpp"
#include "components/hash.hpp"

#include <array>
#include <unordered_map>
#include <generator>
#include <functional>
namespace components {
  template<class V>
  struct Ops  {
  
  };
  
  template<class V>
  concept Value = requires (const V& l, const V& r,std::int8_t v) {
    {Ops<V>::Add(l,r)}->std::convertible_to<V>;
    {Ops<V>::Sub(l,r)}->std::convertible_to<V>;
    {Ops<V>::Div(l,r)}->std::convertible_to<V>;
    {Ops<V>::SDiv(l,r)}->std::convertible_to<V>;
    {Ops<V>::Mul(l,r)}->std::convertible_to<V>;
    {Ops<V>::SLEq(l,r)}->std::convertible_to<V>;
    {Ops<V>::LEq(l,r)}->std::convertible_to<V>;
    {Ops<V>::SGEq(l,r)}->std::convertible_to<V>;
    {Ops<V>::GEq(l,r)}->std::convertible_to<V>;
    {Ops<V>::Eq(l,r)}->std::convertible_to<V>;
    {Ops<V>::NEq(l,r)}->std::convertible_to<V>;
    {Ops<V>::SLt(l,r)}->std::convertible_to<V>;
    {Ops<V>::Lt(l,r)}->std::convertible_to<V>;
    {Ops<V>::SGt(l,r)}->std::convertible_to<V>;
    {Ops<V>::Gt(l,r)}->std::convertible_to<V>;
    {Ops<V>::Negation(l)}->std::convertible_to<V>;
    {Ops<V>::Minus(l)}->std::convertible_to<V>;
    {Ops<V>::undef()} ->std::convertible_to<std::generator<V>>;
    {Ops<V>::symbolise(v)} ->std::convertible_to<V>;
    {Ops<V>::default_val()} ->std::convertible_to<V>;
    
  };
  
  template<Value T>
  class State {
  public:
    static State makeInitialState(const IR::CFA& cfa) {
      std::vector<T> regs;
      for (auto& r : cfa.getRegisters()) {
	regs.emplace_back(Ops<T>::default_val());
      }

      std::array<T,256> memory;
      std::fill(memory.begin(),memory.end(),Ops<T>::default_val());
      return State (cfa.getInitial(),std::move(regs),std::move(memory));  
    }
    
    State (const State& s) = default;
    
    auto readAddr (std::size_t addr) const {return memory.at(addr);}
    
    void writeAddr (std::size_t addr,T val) {memory.at(addr) = val;}

    std::span<const T> getMem () const {
      return memory;
    }
    
    void setRegister (const IR::Register& reg, T val) {
      register_values.at(reg.getNumber()) = val;
    }

    auto getRegisterValue (const IR::Register& reg) const {return register_values.at(reg.getNumber());}

    auto getLocation () const {return location;}
    void setLocation (const IR::Location_ptr l)  {location = l;}

    std::size_t hash (std::size_t seed = 0) const {
      components::HashCombine hasher {seed};
      for (auto& v : register_values)
	hasher << v;
      for (auto& v : memory)
	hasher << v;
      hasher << *location;
      return hasher.get ();
	
    }
    
  private:
    State (IR::Location_ptr initial,
	   std::vector<T>&& register_vals,
	   std::array<T,256>&& memory) : location(initial),
					 register_values(std::move(register_vals)),
					 memory(std::move(memory)) {}
    
    IR::Location_ptr location;
    std::vector<T> register_values;
    std::array<T,256> memory;
  };

  template<class T>
  class StatePrinter {
  public:
    StatePrinter (std::ostream& os, IR::CFA& cfa) : cfa(cfa),os(os) {}
    StatePrinter& operator<< (const State<T>& s) {
      os << s.getLocation()->getName() << std::endl;
      for (auto& r : cfa.getRegisters()) {
	if constexpr (std::is_same_v<T,std::int8_t>) {
	  os << *r << " : " << static_cast<std::int32_t> (s.getRegisterValue (*r)) << std::endl; 
	
	}
	else {
	  os << *r << " : " << s.getRegisterValue (*r) << std::endl; 
	}
      }

      os << "Memory" << std::endl;
      for (auto  m : s.getMem ()) {
	if constexpr (std::is_same_v<T,std::int8_t>) {
	  os << static_cast<std::int32_t> (m) << " "; 
	
	}
	else {
	  os << m; 
	}
      }
      
      os << std::endl;
      return *this;
    }
  private:
    IR::CFA& cfa;
    std::ostream& os;
  };
  
  template<Value V>
  class ExprEvaluator : protected IR::ExprVisitor<std::generator<V> >{
  public:
    ExprEvaluator  (const State<V>& state) : state(&state) {}
    std::generator<V> evaluate (const IR::Expr& expr) {
      for ( auto v : this->visit(expr))
	co_yield v;
    }
    
    std::generator<V> visitRegister (const IR::Register& r) {
      co_yield state->getRegisterValue(r);
    }
    
    virtual std::generator<V> visitConstant (const IR::Constant& r) {co_yield {Ops<V>::symbolise(r.getValue())};}
    
    std::generator<V> visitAddExpr (const IR::AddExpr& r) {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Add));
    }
    
    std::generator<V> visitSubExpr (const IR::SubExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Sub));
    }
    std::generator<V> visitDivExpr (const IR::DivExpr& r) override {
        co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Div));
    }
    std::generator<V> visitSDivExpr (const IR::SDivExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::SDiv));
	
    }
    std::generator<V> visitMulExpr (const IR::MulExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Mul));
    
    }
    std::generator<V> visitLEqExpr (const IR::LEqExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::LEq));
      
    }
    std::generator<V> visitGEqExpr (const IR::GEqExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::GEq));
    
    }
    std::generator<V> visitSLEqExpr (const IR::SLEqExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::SLEq));
    }
    std::generator<V> visitSGEqExpr (const IR::SGEqExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::SGEq));
	
    }
    
    std::generator<V> visitNEqExpr (const IR::NEqExpr& r) override {
        co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::NEq));
	
    }
    std::generator<V> visitEqExpr (const IR::EqExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Eq));
	
    }
    std::generator<V> visitLtExpr (const IR::LtExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Lt));
    
    }
    std::generator<V> visitGtExpr (const IR::GtExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::Gt));
    
    }
    std::generator<V> visitSLtExpr (const IR::SLtExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::SLt));
    
    }
    
    std::generator<V> visitSGtExpr (const IR::SGtExpr& r) override {
      co_yield std::ranges::elements_of (this->BinaryVisit(r,Ops<V>::SGt));
      
    }
    
    std::generator<V> visitNegationExpr (const IR::NegationExpr& r) override {
      for (auto t : this->visit(r.getInner ()))
	co_yield Ops<V>::Negation (t);
    }
    std::generator<V> visitMinusExpr (const IR::MinusExpr& r) override {
      for (auto t : this->visit(r.getInner ()))
	co_yield Ops<V>::Minus (t);
    }

    virtual std::generator<V> visitDerefExpr (const IR::DerefExpr& r) override {
      co_yield std::ranges::elements_of (Ops<V>::undef());
      
    }
    
    std::generator<V> visitUndefExpr (const IR::Undef& r) override {
      co_yield std::ranges::elements_of (Ops<V>::undef());
    }
    
  private:
    template<class T>
    std::generator<V> BinaryVisit (const T& b,std::function<V(const V&,const V&)> func ) {
      for (auto l : this->visit(b.getLeft())){
	for (auto r : this->visit(b.getRight())) {
	  co_yield func (l,r);
	  
	}
      }
    }
  protected:
    const State<V>* state;
  };

  
}


#endif
