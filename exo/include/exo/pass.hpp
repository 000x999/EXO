#ifndef PASS_HPP
#define PASS_HPP 

#include "exir/graph.hpp"
#include "exir/verifier.hpp"
#include <string>

namespace exo{

class pass{
public:
  virtual            ~pass      ()                      = default; 
  virtual std::string pass_name () const                = 0;
  virtual bool        run_pass  (exir::graph &graph_in) = 0; 
}; 

}; //namespace 
#endif 
