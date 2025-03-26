#ifndef _IR__CFA__
#define _IR__CFA__

#include "ir/instructions.hpp"

#include <vector>
#include <unordered_set>
#include <sstream>
#include <ranges>
  namespace IR {
    class Location;
    using Location_ptr = std::shared_ptr<Location>;
    class Edge {
    public:
      Edge (Instruction_ptr&& instr, Location_ptr to) : to(to),instruction(std::move(instr)) {}
      
      auto& getInstruction () const {return instruction;};
      auto& getTo () const {return to;}
      
    private:
      Location_ptr to;
      Instruction_ptr instruction;
    };
    
    
    class Location {
      public:
      void setName (const std::string name) {this->name = name;}
      
      auto& getName () const {return name;}
      void addEdge (Instruction_ptr&& instr, Location_ptr to) {
	_edges.emplace_back (std::move(instr),to);
      }

      const auto& edges () const {return _edges;}
      auto isAssert () const {return _assert;}
      std::size_t hash () const {return reinterpret_cast<std::size_t> (this);}
      std::ostream& output ( std::ostream& os) {
	return os << name  << ((_assert ) ? ":-("  :   ":-)");
      }
    protected:
      Location (std::string name, bool asser = false) : name(std::move(name)),_assert(asser) {}
      
    private:
      friend class CFA;
      std::string name;
      std::vector<Edge> _edges;
      bool _assert;
    };

    class CFA {
    public:
      CFA ()  {}
      
      auto makeLocation (std::string name, bool isInitial, bool assert = false) {
	locations.emplace_back (std::shared_ptr<Location> (new Location(makeFresh(name),assert)));
	if (isInitial)
	  initial = locations.back ();
	return locations.back ();
      }

      auto makeRegister (std::string name) {
	registers.emplace_back (std::make_shared<Register> (registers.size(),name));
	return registers.back ();
      }

      auto getInitial ()const  {
	return initial;
      }

      auto& getRegisters () const {return registers;}
      
    private:
      std::string makeFresh( const std::string& s) {
	
	std::string res = s;
	std::size_t i = 0;
	while(loc_names.count(res) || res =="") {
	  std::stringstream str;
	  str << s << "_" << i;
	  res = str.str();
	  i++;
	}
	loc_names.insert(res);
	return res;
	
      
      
      }
      std::unordered_set<std::string> loc_names;
      std::vector<Location_ptr> locations;
      std::vector<Register_ptr> registers;
      Location_ptr initial{nullptr};
    };
    
    std::ostream& operator<< (std::ostream&, const CFA&);
    
  }
  
 

#endif
