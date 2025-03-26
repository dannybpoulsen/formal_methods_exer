#include "components/uninit.hpp"
#include "components/notsolver.hpp"


namespace uninit {
  Values join (Values l, Values r) {
    throw NotSolvedYet {__FILE__};  
  }
  
}

namespace components {
  

  uninit::Values Ops<uninit::Values>::Add(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};
  }
  
  uninit::Values Ops<uninit::Values>::Sub(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};
  }

  uninit::Values Ops<uninit::Values>::Div(const uninit::Values &l, const uninit::Values &r) {
      throw NotSolvedYet {__FILE__};
  }

  uninit::Values Ops<uninit::Values>::SDiv(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}
  
  uninit::Values Ops<uninit::Values>::Mul(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::SLEq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::LEq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::SGEq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::GEq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::SLt(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::Lt(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::SGt(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::Gt(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::Eq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::NEq(const uninit::Values &l, const uninit::Values &r) {
    throw NotSolvedYet {__FILE__};}

  uninit::Values Ops<uninit::Values>::Negation(const uninit::Values &t) {   throw NotSolvedYet {__FILE__};
   }

  uninit::Values Ops<uninit::Values>::Minus(const uninit::Values &t) {   throw NotSolvedYet {__FILE__};
  }
  uninit::Values Ops<uninit::Values>::symbolise(std::int8_t) {   throw NotSolvedYet {__FILE__};
   }
  
  std::generator<uninit::Values> Ops<uninit::Values>::undef() {
      throw NotSolvedYet {__FILE__};
  
  }
}
  
namespace uninit {
  std::generator<uninit::Values> Evaluator::visitDerefExpr (const IR::DerefExpr& r)  {
    throw NotSolvedYet {__FILE__};
  
  }
  
  
  
  std::generator<State> Transfer::visitAssume (const IR::Assume&)
  {
      throw NotSolvedYet {__FILE__};
  }
  
  std::generator<State> Transfer::visitStore (const IR::Store& s) {
        throw NotSolvedYet {__FILE__};
  }
  
  
}

