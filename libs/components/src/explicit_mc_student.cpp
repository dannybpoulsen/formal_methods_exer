#include "components/explicit_mc.hpp"
#include "components/notsolver.hpp"

namespace components {
  std::int8_t Ops<std::int8_t>::Add(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Sub(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Div(const std::int8_t &l, const std::int8_t &r) {
    return std::bit_cast<std::int8_t>(static_cast<std::int8_t>(
							       std::bit_cast<std::uint8_t>(l) / std::bit_cast<std::uint8_t>(r)));
  }
  
  std::int8_t Ops<std::int8_t>::SDiv(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Mul(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::SLEq(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::LEq(const std::int8_t &l, const std::int8_t &r) {
    return std::bit_cast<std::int8_t>(std::bit_cast<std::uint8_t>(l) <=
				      std::bit_cast<std::uint8_t>(r));
  }
  
  std::int8_t Ops<std::int8_t>::SGEq(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::GEq(const std::int8_t &l, const std::int8_t &r) {
    return std::bit_cast<std::int8_t>(std::bit_cast<std::uint8_t>(l) >=
				      std::bit_cast<std::uint8_t>(r));
  }
  
  std::int8_t Ops<std::int8_t>::SLt(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Lt(const std::int8_t &l, const std::int8_t &r) {
    return std::bit_cast<std::int8_t>(std::bit_cast<std::uint8_t>(l) <
				      std::bit_cast<std::uint8_t>(r));
  }
  
  std::int8_t Ops<std::int8_t>::SGt(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Gt(const std::int8_t &l, const std::int8_t &r) {
    return std::bit_cast<std::int8_t>(std::bit_cast<std::uint8_t>(l) >
				      std::bit_cast<std::uint8_t>(r));
  }
  
  std::int8_t Ops<std::int8_t>::Eq(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::NEq(const std::int8_t &l, const std::int8_t &r) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Negation(const std::int8_t &t) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::int8_t Ops<std::int8_t>::Minus(const std::int8_t &t) {
    throw NotSolvedYet{__FILE__};
  }
  
  std::generator<std::int8_t> Ops<std::int8_t>::undef() {
    auto i = std::numeric_limits<std::int8_t>::min();
    for (; i < std::numeric_limits<std::int8_t>::max(); ++i)
      co_yield i;
    co_yield i;
  }
  
  namespace explic {
    std::generator<std::int8_t> Evaluator::visitDerefExpr(const IR::DerefExpr &r) {
      throw NotSolvedYet{__FILE__};
    }
    
    std::generator<State> Transfer::visitAssume(const IR::Assume &s) {
      throw NotSolvedYet{__FILE__};
    }
    
    std::generator<State> Transfer::visitStore(const IR::Store &s) {
      throw NotSolvedYet{__FILE__};
    }
    
  } // namespace explic
  
} // namespace components
