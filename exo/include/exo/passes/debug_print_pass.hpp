#ifndef DEBUG_PRINT_PASS_HPP 
#define DEBUG_PRINT_PASS_HPP 
#include "exo/pass.hpp"
namespace exo{
class debug_print_pass: public exo::pass{
public: 
  debug_print_pass      ()                    = default; 
  ~debug_print_pass     () override           = default; 
  std::string pass_name ()                const override;
  bool        run_pass  (exir::graph &graph_in) override;
};
}; //namespace 
#endif 
