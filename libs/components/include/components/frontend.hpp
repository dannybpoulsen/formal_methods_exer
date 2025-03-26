#include "whiley/ast.hpp"

#include <expected>



namespace components {
  enum class LoadError 
    {
      TypeError,
      ParseError
    };
  
  std::expected<Whiley::Program,LoadError> loadProgram (const std::string& filename);
  
  
}
