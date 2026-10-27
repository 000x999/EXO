#include "exir/graph.hpp"
#include "exir/verifier.hpp"
#include "exo/passes/debug_print_pass.hpp"
#include "exo/pass_manager.hpp"
#include <iostream>

int test_accept(){
  exir::graph g;
  auto input   = g.add_value(exir::tensor_type{{2, 3}, exir::dtype::int32}, "input");
  auto weight  = g.add_value(exir::tensor_type{{3, 4}, exir::dtype::int32}, "ffn_w1");
  auto lin_out = g.add_value(exir::tensor_type{{2, 4}, exir::dtype::int32}, "lin_out");
  auto output  = g.add_value(exir::tensor_type{{},     exir::dtype::int32}, "output");
  
  g.add_node(exir::op_kind::input   , {}             , {input}  , "model_input"   ); 
  g.add_node(exir::op_kind::constant, {}             , {weight}  , "weight"       ); 
  g.add_node(exir::op_kind::linear  , {input, weight}, {lin_out} , "lin_0"        ); 
  g.add_node(exir::op_kind::output  , {lin_out}     , {output}  , "model_output" );
  
  //g.print();
  
  exo::pass_manager pm;
  pm.add_pass(std::make_unique<exo::debug_print_pass>());
  
  if(!pm.run_pass(g)){
    return 1; 
  }

  if(!exir::verify_graph(g)){
    std::cerr << "::EXIR VERIF FAILED::\n";
    return 1; 
  }
  

  std::cout << ":: EXIR VERIF OK ::\n";
  std::cout << ":: EXO SANITY OK ::\n"; 
  return 0; 
}

int main(){
  test_accept();
}
