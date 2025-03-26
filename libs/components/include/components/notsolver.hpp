#ifndef _NOT_SOLVED__
#define _NOT_SOLVED__
#include <fmt/core.h>
#include <stdexcept>

class NotSolvedYet : public std::runtime_error {
public:
  NotSolvedYet (const std::string& s) : std::runtime_error (fmt::format ("Tasknot solved. Go to  {} for adding your solution",s)) {}
  
  
  
};



#endif
