#ifndef _SIMULATOR__
#define _SIMULATOR__


#include "ir/cfa.hpp"
#include "components/state.hpp"
#include "components/transfer.hpp"

#include <memory>
#include <generator>
#include <iostream>

template<components::Value V,class Transfer>
class Simulator {
public:
  Simulator (IR::CFA& cfa,Transfer& transfer) : cfa(cfa),current(components::State<V>::makeInitialState(cfa)),transfer(transfer)  {
  }
  
  void startSimulation ()  {current = components::State<V>::makeInitialState(cfa);}

  void showState ()  {
    components::StatePrinter<V> {std::cout, cfa} << current;
  }

  void step () {
    std::vector<components::State<V>> states;
    for (auto s : transfer(current)) {
      states.push_back(s);
    }
    if (states.size ())
      current = states.at(0);
  }
  
  
private:
  IR::CFA& cfa;
  components::State<V> current;
  Transfer& transfer;
};

template<components::Value V,class Transfer>
class Command {
public:
  virtual bool execute (Simulator<V,Transfer>* simu) {return true;}
};

template<components::Value V,class Transfer>
class ShowStateCommand : public Command<V,Transfer> {
public:
  bool execute(Simulator<V,Transfer> *simu) override {
    simu->showState();
    return true; }
};

template<components::Value V,class Transfer>
class StartSimulation : public Command<V,Transfer> {
public:
  StartSimulation() {}
  bool execute(Simulator<V,Transfer> *simu) override {
    simu->startSimulation ();
    return true; }
};

template<components::Value V,class Transfer>
class StepSimulation : public Command<V,Transfer> {
public:
  StepSimulation() {}
  bool execute(Simulator<V,Transfer> *simu) override {
    simu->step ();
    return true; }
};

class CommandBuilder {
public:
  virtual void startSimulation()= 0;

  virtual void showState() = 0;
  
  virtual void step() = 0;

  virtual void skip() = 0;

};

template<components::Value V,class Transfer>
class VCommandBuilder : public CommandBuilder {
public:
  VCommandBuilder() {}
  void startSimulation() { cmd = std::make_unique<StartSimulation<V,Transfer>>(); }

  void showState() { cmd = std::make_unique<ShowStateCommand<V,Transfer>>(); }

  void step() { cmd = std::make_unique<StepSimulation<V,Transfer>>(); }

  void skip() { cmd = std::make_unique<Command<V,Transfer>>(); }

  auto get() { return std::move(cmd); }

private:
  std::unique_ptr<Command<V,Transfer>> cmd{nullptr};
};


std::string readline();
void doParse (CommandBuilder& builder);

template<components::Value V,class Transfer>
class CommandParser {
public:
  CommandParser ()  {}
  std::unique_ptr<Command<V,Transfer>> parse() {
    VCommandBuilder<V,Transfer> builder;
    doParse (builder);
    
    auto cmd = builder.get();
    if (cmd)
      return cmd;
    
    
    return nullptr;
  }
  
  
  
};
    
    

#endif
