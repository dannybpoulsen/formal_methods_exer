#include "ir/cfa.hpp"
#include "components/frontend.hpp"
#include "components/compiler.hpp"
#include "components/state.hpp"
#include "components/transfer.hpp"
#include "components/explicit_mc.hpp"
#include "simulator.hpp"

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
	
	Simulator<std::int8_t,components::explic::Transfer> simulator {cfa,transfer};
	CommandParser<std::int8_t,components::explic::Transfer> parser;
	auto command = parser.parse ();
	  
	while (command) {
	  command->execute (&simulator);
	  command = parser.parse ();
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
