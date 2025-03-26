#include "ir/cfa.hpp"
#include "components/frontend.hpp"
#include "components/compiler.hpp"
#include "components/state.hpp"
#include "components/transfer.hpp"
#include "components/explicit_mc.hpp"
#include "components/search.hpp"

#include <bit>
#include <iomanip>




int main (int argc, char** argv) {
  try {
    if (argc > 1) { 
      auto res = components::loadProgram (argv[1]);
      if (res.has_value ()) {
	auto cfa = components::Compiler{}.Compile(*res);
	components::explic::State initial_state = components::State<std::int8_t>::makeInitialState (cfa);
	components::explic::StatePrinter printer {std::cout,cfa};
	
	auto predicate = [&printer](const components::explic::State& s) {
	  if (s.getLocation()->isAssert ()) {
	    return true;
	  }
	  return false;
	};
	components::Reachability<std::int8_t,components::explic::Transfer> reach {components::explic::Transfer{}};
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
