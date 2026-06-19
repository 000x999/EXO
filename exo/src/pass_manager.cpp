#include "exo/pass_manager.hpp"
#include <iostream>

void exo::pass_manager::add_pass(std::unique_ptr<exo::pass> pass_in){
  passes.push_back(std::move(pass_in)); 
}

bool exo::pass_manager::run_pass(exir::graph &graph_in){
  for(auto &pass : passes){
    std::cout << "::EXO PASS MANAGER:: Running pass " << pass->pass_name() << "\n";
    bool is_changed = pass->run_pass(graph_in); 
    
   // if(is_changed){
      if(!exir::verify_graph(graph_in)){
        std::cerr << "::EXO PASS MANAGER:: Graph invalid after pass" << pass->pass_name() << "\n";
        return false; 
      }
    //}

    std::cout << "::EXO PASS MANAGER:: Pass :: " << pass->pass_name() 
              << " Changed graph: "              << (is_changed ? "true" : "false") 
              << "\n";  

  }
  return true; 
}
