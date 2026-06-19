#include "exo/passes/debug_print_pass.hpp"
#include <iostream>

std::string exo::debug_print_pass::pass_name() const{
  return "debug_print_pass";
}

bool exo::debug_print_pass::run_pass(exir::graph &graph_in){
  std::cout << "::EXO PASS:: Running debug print pass\n"; 
  graph_in.print();

  return false; 
}
