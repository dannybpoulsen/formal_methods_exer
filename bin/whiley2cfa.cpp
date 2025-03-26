#include "ir/cfa.hpp"
#include "components/frontend.hpp"
#include "components/compiler.hpp"


int main (int argc, char** argv) {
  try {
    if (argc > 1) { 
      auto res = components::loadProgram (argv[1]);
      if (res.has_value ()) {
	auto cfa = components::Compiler{}.Compile(*res);
	std::cerr << cfa << std::endl;
	
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
