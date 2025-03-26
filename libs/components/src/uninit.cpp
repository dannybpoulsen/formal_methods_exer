#include "components/uninit.hpp"


namespace uninit {
  Values join (Values l, Values r) {
    if (l == Values::Uninitialised || r == Values::Uninitialised)
      return Values::Uninitialised;
    else
      return Values::Initialised;
  }
  
}

namespace components {
  

  uninit::Values Ops<uninit::Values>::Add(const uninit::Values &l, const uninit::Values &r) {
    return join (l,r);
  }
  
  uninit::Values Ops<uninit::Values>::Sub(const uninit::Values &l, const uninit::Values &r) {
    return join (l,r);
  }

  uninit::Values Ops<uninit::Values>::Div(const uninit::Values &l, const uninit::Values &r) {
    return join (l,r);
  }

  uninit::Values Ops<uninit::Values>::SDiv(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}
  
  uninit::Values Ops<uninit::Values>::Mul(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::SLEq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::LEq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::SGEq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::GEq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::SLt(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::Lt(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::SGt(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::Gt(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::Eq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::NEq(const uninit::Values &l, const uninit::Values &r) {
  return join (l,r);}

  uninit::Values Ops<uninit::Values>::Negation(const uninit::Values &t) { return t; }

  uninit::Values Ops<uninit::Values>::Minus(const uninit::Values &t) { return t; }
  uninit::Values Ops<uninit::Values>::symbolise(std::int8_t) { return uninit::Values::Initialised; }
  
  std::generator<uninit::Values> Ops<uninit::Values>::undef() {
    co_yield uninit::Values::Initialised;
  }
}
  
namespace uninit {
  std::generator<uninit::Values> Evaluator::visitDerefExpr (const IR::DerefExpr& r)  {
    co_yield Values::Initialised;
    
  }
  
  
  
  std::generator<State> Transfer::visitAssume (const IR::Assume&)
  {
    co_yield State(_internal->state);
  }
  
  std::generator<State> Transfer::visitStore (const IR::Store& s) {
    co_yield State(_internal->state);
  }
  
  
}

