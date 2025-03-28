#include "ir/cfa.hpp"
#include "components/state.hpp"
#include "components/notsolver.hpp"
#include <optional>
#include <functional>
#include <unordered_map>
#include <vector>
#include <list>
#include <stack>

namespace components {

  template<Value V>
  struct TraceData {
    TraceData (State<V> state, IR::Edge* e = nullptr) : state(state),edge(e) {}
    State<V> state;
    const IR::Edge* edge;
  };
  
  
  template<Value V>
  using Predicate = std::function<bool(const State<V>&)>;
  template<Value V,class Transfer>
  class Reachability {
  public:
    Reachability (Transfer&& f) : transfer(std::move(f)) {}
    std::optional<State<V>> search (State<V>&, Predicate<V> );
    std::list<TraceData<V> > buildTraceTo (const State<V>&, const State<V>&);
  private:
    std::unordered_set<std::size_t> visited;
    Transfer transfer;
  };

#ifdef SOLUTION
#include "components/search_implementation.hpp"
#else
#include "components/search_implementation_student.hpp"
#endif

  
  template<Value V,class Transfer>
  inline std::list<TraceData<V>> Reachability<V,Transfer>::buildTraceTo (const State<V>& from, const State<V>& goal) {
    std::list<TraceData<V>> trace;
    std::unordered_set<std::size_t> explored;
    std::unordered_set<std::size_t> on_stack;
    
    trace.emplace_back (from);
    on_stack.insert(from.hash());
    while (trace.size()) {
      auto state = trace.back();
      if ( explored.count(state.state.hash ())) {
	//We are done exploring for this state
	trace.pop_back();
      }
      else if (state.state.hash() == goal.hash ()) {
	//Found the goal
	return trace;
      }
      else {
	bool succ = false;
	for (auto& e : state.state.getLocation()->edges()) {
	  for (auto s : transfer (state.state,e)) {
	    if (!explored.count(s.hash()) && !on_stack.count(s.hash()) && visited.count(s.hash())) {
	      succ = true;
	      trace.back().edge = &e;
	      trace.push_back(s);
	      on_stack.insert(s.hash());
	      break;
	    }
	    
	  }
	  if (succ)
	    break;
	}
	if (!succ) {
	  trace.back().edge = nullptr;
	  explored.insert(state.state.hash());
	}
	  
      }
    }
    throw std::runtime_error ("Trace Generation Failed");
  }
  
}
