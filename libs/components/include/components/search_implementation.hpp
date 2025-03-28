template<Value V,class Transfer>
inline std::optional<State<V>> Reachability<V,Transfer>::search (State<V>& init, Predicate<V> pred) {
  std::vector<State<V>> waiting;
  visited.clear();
  auto addState = [&waiting,this](const State<V>& s) {
    auto hash = s.hash ();
    if (!visited.count(hash)) {
      visited.insert(hash);
      waiting.push_back(s);
    }
  };

  
  addState(init);
  while (waiting.size()) {
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
