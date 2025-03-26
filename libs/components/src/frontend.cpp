#include "components/frontend.hpp"
#include "whiley/parser.hpp"
#include "whiley/typechecker.hpp"

#include <expected>


namespace components {
  std::expected<Whiley::Program,LoadError> loadProgram (const std::string& filename) {
    
    auto parse_res = Whiley::WParser{}.parse(filename);
    
    if (!parse_res)
      return std::unexpected{LoadError::ParseError};
    auto prgm = parse_res.get();
    if (Whiley::TypeChecker{}.CheckProgram (prgm))
      return prgm;
    else return std::unexpected{LoadError::TypeError};
  }
}
