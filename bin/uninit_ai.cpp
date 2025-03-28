#include "ir/cfa.hpp"
#include "components/frontend.hpp"
#include "components/compiler.hpp"
#include "components/state.hpp"
#include "components/transfer.hpp"
#include "components/uninit.hpp"
#include "components/search.hpp"

#include <bit>
#include <iomanip>




int main (int argc, char** argv) {
  try {
    if (argc > 1) { 
      auto res = components::loadProgram (argv[1]);
      if (res.has_value ()) {
	auto cfa = components::Compiler{}.Compile(*res);
	uninit::State initial_state = uninit::State::makeInitialState (cfa);
	uninit::StatePrinter printer {std::cout,cfa};
	
	
	auto predicate = [](const uninit::State& s) {
	  for (auto& e : s.getLocation()->edges ()) {
	    if (e.getInstruction ()->instType () == IR::Assume::opcode()) {
	      auto instr = std::static_pointer_cast<IR::Assume> (e.getInstruction());
	      uninit::Evaluator evaluator {s};
	      for (auto val : evaluator.evaluate (instr->getExpression())) {

		if (val == uninit::Values::Uninitialised)
		  return true;
	      }
	    }
	  }
	    
	  return false;
	};
	
	components::Reachability<uninit::Values,uninit::Transfer> reach {uninit::Transfer{}};
	auto res = reach.search (initial_state,predicate);
	
	if (res) {
	    
	  auto trace = reach.buildTraceTo (initial_state,res.value());
	  for (auto s : trace)  {
	    printer << s.state;
	    std::cout << "\n\n";
	      
	    if (s.edge)
	      std::cout << *s.edge->getInstruction() << "--->\n";  
	    std::cout << "\n\n";
	  }
	}
	
      }
      
    }
    else
      return -1;
  }
  catch (std::runtime_error& r) {
    std::cerr << r.what() << std::endl;
    return -1;
  }
}
