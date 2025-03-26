#include "simulator.hpp"
#include "scanner.h"
#include "parser.hh"
    
#include <readline/readline.h>
#include <readline/history.h>

std::string readline() {
  char* buf = ::readline (">");
  if (buf) {
    std::string res (buf);
    free(buf);
    return res;
  }
  return std::string{};
}


void doParse (CommandBuilder& builder) {
  std::string line = readline();
    
  std::stringstream stream;
  stream.str(line);
  Scanner scanner {&stream};
  yy::Parser parser{scanner,builder};
  parser.parse ();
}
