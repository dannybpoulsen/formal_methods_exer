%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {yy}
%define api.parser.class {Parser}


%code requires{
  class Scanner;
  class CommandBuilder;
  


#include <cstdint>
#include <string>
    
 }

%parse-param { Scanner& scanner } {CommandBuilder& builder} 
%initial-action
{

};

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include "scanner.h"
  #include "commands.hpp"
#undef yylex
#define yylex scanner.yylex
  
}



%define api.value.type variant
%define parse.assert

%token    START_SIMULATION 
%token    SHOW_STATE
%token    SHOW_TRANSITIONS
%token    STEP
%token    SEARCH
%token    SYMBOLIC



%token <std::int64_t> POS_NUMBER
%token <std::int64_t> NEG_NUMBER

%token END 0 "end of file"


%%

prgm : START_SIMULATION {builder.startSimulation ();} |
       SHOW_STATE {builder.showState();} |
       STEP {builder.step ();} |
       
       error  {builder.skip ();}

%%


void  yy::Parser::error(const std::string &err_message )
{
  std::cerr << err_message;
}
