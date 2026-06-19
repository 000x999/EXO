#ifndef PASS_MANAGER_HPP 
#define PASS_MANAGER_HPP

#include "exir/graph.hpp"
#include "exo/passes/debug_print_pass.hpp"
#include "exir/verifier.hpp"
#include "exo/pass.hpp"
#include <vector> 
#include <memory> 

namespace exo{
class pass_manager{
public: 
  pass_manager  () = default; 
  void add_pass (std::unique_ptr<pass> pass_in);
  bool run_pass (exir::graph &graph_in);

private: 
  std::vector<std::unique_ptr<exo::pass>> passes;   
  
};
}; //namespace 
#endif 
