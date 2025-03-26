#ifndef _TRANSFER__
#define _TRANSFER__

#include "components/state.hpp"

#include <generator>
#include <memory>

namespace components {
  template<Value V,class Evaluator = ExprEvaluator<V>>
  class Transfer : private IR::InstructionVisitor<std::generator<State<V>>>  {
  public:
    std::generator<State<V>> operator() (const State<V>&s, const IR::Edge& e) {
      auto  data = std::make_unique<Internal> (s);
      _internal = data.get();
	for (auto s : this->visit (*e.getInstruction ())) {
	  s.setLocation (e.getTo ());
	  co_yield s;
	}
    }
    

    std::generator<State<V>> operator() (const State<V>&s) {
      auto  data = std::make_unique<Internal> (s);
      _internal = data.get();
      for (auto& e : s.getLocation()->edges()) {
	co_yield std::ranges::elements_of((*this)(s,e));
      }
    }
    
    virtual std::generator<State<V>> visitAssign (const IR::Assign& ass) override {
      State<V> nstate(_internal->state);
      for (auto e : _internal->evaluator.evaluate (ass.getExpression())) {
	State<V> nstate(_internal->state);
	
	nstate.setRegister (ass.getDestination(),e);
	co_yield nstate;
      }
    }
    
    virtual std::generator<State<V>> visitAssume (const IR::Assume& s) override {
      State<V> nstate(_internal->state);
      co_yield nstate;
    }

    virtual std::generator<State<V>> visitSkip (const IR::Skip&) override {
      State<V> nstate(_internal->state);
      co_yield nstate;
    }
    
    virtual std::generator<State<V>> visitStore (const IR::Store&) override {
      State<V> nstate(_internal->state);
      co_yield nstate;
      
    }
    
  protected:
    struct Internal {
      Internal (const State<V>& s) : evaluator(s),state(s) {}
      Evaluator evaluator;
      const State<V>& state;
    };
    
    Internal* _internal;
  };
} // namespace components


#endif
