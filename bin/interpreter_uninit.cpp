#include "ir/cfa.hpp"
#include "components/frontend.hpp"
#include "components/compiler.hpp"
#include "components/state.hpp"
#include "components/transfer.hpp"
#include "components/uninit.hpp"
#include "simulator.hpp"

#include <bit>
#include <iomanip>


int main (int argc, char** argv) {
  try {
    if (argc > 1) { 
      auto res = components::loadProgram (argv[1]);
      if (res.has_value ()) {
	auto cfa = components::Compiler{}.Compile(*res);
	uninit::State initial_state = uninit::State::makeInitialState (cfa);
	uninit::Transfer transfer;
	
	Simulator<uninit::Values,uninit::Transfer> simulator {cfa,transfer};
	CommandParser<uninit::Values,uninit::Transfer> parser;
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
