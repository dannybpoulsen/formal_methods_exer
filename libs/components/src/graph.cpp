#include "components/graph.hpp"

#include <graphviz/cgraph.h>
#include <sstream>

namespace components {
  struct Location::Internal {
    Internal (Agnode_t* node, Agraph_t* graph) : node(node),graph(graph) {};
    ~Internal () {};
    Agnode_t* node;
    Agraph_t* graph;
  };

  Location::Location (std::unique_ptr<Internal>&& _int) : _internal(std::move(_int)) {}
  Location::~Location ()  {}
  Location::Location (Location&&) = default;
    
  void Location::addEdge (const IR::Instruction& instruction, const Location& to) {
    std::stringstream str;
    str << instruction;
    auto edge = agedge (_internal->graph,_internal->node,to._internal->node,const_cast<char*>(str.str().c_str()),1);
    agset (edge,const_cast<char*> ("label"),const_cast<char*>(str.str().c_str()));	
    
  }
  
  
  
  
  struct Graph::Internal {
    Internal (const std::string& s) {
      graph = agopen(const_cast<char*> (s.c_str()), Agdirected, NULL);
      agattr(graph,AGEDGE,const_cast<char*>("label"),const_cast<char*> (""));
      agattr(graph,AGNODE,const_cast<char*>("label"),const_cast<char*>(""));
      agattr(graph,AGNODE,const_cast<char*>("shape"),const_cast<char*>(""));
      agattr(graph,AGNODE,const_cast<char*>("color"),const_cast<char*>("black"));
      agattr(graph,AGNODE,const_cast<char*>("fillcolor"),const_cast<char*>("white"));
      agattr(graph,AGNODE,const_cast<char*>("style"),const_cast<char*>("filled"));
    };
    ~Internal () {
      agclose(graph);
    };

    Agraph_t* graph;
  };

  Graph::Graph (const std::string& s) {
    _internal = std::make_unique<Internal> (s);
  }

  Graph::~Graph () {}

  Location Graph::makeLocation (const std::string& name,const std::string& label) {
    
    auto node = agnode(_internal->graph,const_cast<char*>(name.c_str()),1);
    agset (node,const_cast<char*> ("label"),const_cast<char*>(label.c_str()));	
    return {std::make_unique<Location::Internal> (node,_internal->graph)};
  }

  std::ostream& Graph::write (std::ostream& os) const {
    char* buf;
    size_t len;
    auto out = open_memstream(&buf,&len);
    agwrite (_internal->graph,out);
    os << buf;
    fclose (out);
    free (buf);
    return os;
  }
    
  
}
