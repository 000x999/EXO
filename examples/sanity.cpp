#include "exir/graph.hpp"
#include "exir/verifier.hpp"
#include <iostream>

int main(){
  exir::graph g;
  auto input    = g.add_value(exir::tensor_type{{1  , 768} , exir::dtype::float32}, "input"   );
  auto weight   = g.add_value(exir::tensor_type{{768, 3072}, exir::dtype::float32}, "ffn_w1"  );
  auto lin_out  = g.add_value(exir::tensor_type{{1  , 3072}, exir::dtype::float32}, "lin_out" ); 
  auto relu_out = g.add_value(exir::tensor_type{{1  , 3072}, exir::dtype::float32}, "relu_out");
  auto output   = g.add_value(exir::tensor_type{{1  , 3072}, exir::dtype::float32}, "output"  );

  g.add_node(exir::op_kind::input   , {}             , {input}  , "model_input"   ); 
  g.add_node(exir::op_kind::constant, {}             , {weight}  , "weight"       ); 
  g.add_node(exir::op_kind::linear  , {input, weight}, {lin_out} , "lin_0"        ); 
  g.add_node(exir::op_kind::relu    , {lin_out}      , {relu_out}, "relu_0"       ); 
  g.add_node(exir::op_kind::output  , {relu_out}     , {output}  , "model_output" );

  g.print();

  if(!exir::verify_graph(g)){
    std::cerr << "::EXIR VERIF FAILED::\n";
    return 1; 
  }
  std::cout << ":: EXIR VERIF OK ::\n";
  std::cout << ":: EXO SANITY OK ::\n"; 
  return 0;
}
