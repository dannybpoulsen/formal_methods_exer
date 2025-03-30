template<Value V,class Transfer>
inline std::optional<State<V>> Reachability<V,Transfer>::search (State<V>& init, Predicate<V> pred) {
  std::list<State<V>> waiting;
  visited.clear();
  auto addState = [&waiting,this](const State<V>& s) {
    auto hash = s.hash ();
    if (!visited.count(hash)) {
      visited.insert(hash);
      waiting.push_front(s);
    }
  };

  
  addState(init);
  while (waiting.size()) {
    std::cerr << waiting.size() << " " << visited.size () << "\r";
    
    State<V> state = waiting.back();
    waiting.pop_back();
    if (pred(state))
      {
	return state;
      }
    else {
      for (auto s : transfer(state)) {
	addState(s);
	
      }
    }
  }
  
  return std::nullopt;
}
