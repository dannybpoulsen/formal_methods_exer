#include <memory>
#include <iosfwd>
#include "ir/instructions.hpp"

namespace components {
  class Location {
  public:
    struct Internal;
    
    Location (std::unique_ptr<Internal>&& _int );
    ~Location ();
    Location (Location&&);
    void addEdge (const IR::Instruction& expr, const Location& to);
  private:
    std::unique_ptr<Internal> _internal;
  };
  
  
  class Graph {
  public:
    Graph (const std::string&);
    ~Graph ();
    Graph (const Graph&) = delete;
    Graph (Graph&&) = delete;
    std::ostream& write (std::ostream& os) const;
    Location makeLocation (const std::string& name,const std::string& label); 
  private:
    struct Internal;
    std::unique_ptr<Internal> _internal;
  };

  inline std::ostream& operator<< (std::ostream& os, const Graph& g) {
    return g.write (os);
  }
  
}
