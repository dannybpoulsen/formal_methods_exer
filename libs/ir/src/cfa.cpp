#include "ir/cfa.hpp"
#include "components/graph.hpp"
#include <unordered_set>
#include <sstream>
#include <vector>


namespace IR {
  struct EdgeS {
    EdgeS (IR::Location_ptr f, const IR::Edge* edge) : from(f),edge(edge) {}
    IR::Location_ptr from;
    const IR::Edge* edge;
  };
  
  std::ostream& operator<< (std::ostream& os , const CFA& cfa) {
    std::vector<IR::Location_ptr> visited;
    std::vector<IR::Location_ptr> waiting;
    std::vector<EdgeS> edges;
    components::Graph graph {"cfa"};
    
    auto addLocation = [&graph,&visited,&waiting](IR::Location_ptr loc) {
      std::stringstream str;
      str << loc;
      auto gloc = graph.makeLocation (str.str(),loc->getName());
      if (std::find(visited.begin(),visited.end(),loc) == visited.end()) {
	visited.push_back(loc);
	waiting.push_back(loc);
      }
      
      return gloc;
      
    };

    auto findGraphLocation = [&graph,&visited,&waiting](IR::Location_ptr loc) {
      std::stringstream str;
      str << loc;
      return graph.makeLocation (str.str(),loc->getName());
    };
    
    addLocation (cfa.getInitial ());
    while (waiting.size()) {
      auto cur = waiting.back();
      auto gloc = findGraphLocation (cur);
      waiting.pop_back();

      for (const auto& e : cur->edges()) {
	edges.emplace_back (cur,&e);
	auto nloc = addLocation(e.getTo ());
	gloc.addEdge (*e.getInstruction (),nloc);
      }
      
    }

    return os  << graph;
    
  }
    
}
