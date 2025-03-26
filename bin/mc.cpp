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
	components::explic::Transfer transfer;
	components::explic::StatePrinter printer {std::cout,cfa};
	
	auto predicate = [&printer](const components::explic::State& s) {
	  if (s.getLocation()->isAssert ()) {
	    return true;
	  }
	  return false;
	};
	auto res = components::search<std::int8_t> (initial_state,transfer,predicate);
	
	if (res) {
	  printer << res.value();
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
