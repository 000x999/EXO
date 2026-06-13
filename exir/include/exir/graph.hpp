#ifndef GRAPH_HPP
#define GRAPH_HPP 

#include <cstdint> 
#include <string> 

namespace exir_graph{
enum class dtype{
  float32, 
  int8, 
  uint8, 
  int32
};

enum class op_kind{
  input, 
  constant, 
  linear, 
  relu, 
  output
}; 

struct tensor_type{
  int64_t *shape; 
  dtype element = dtype::float32; 
}; 

using value_id = uint32_t; 
using node_id  = uint32_t; 

struct value{
  value_id    id   {};
  tensor_type type {};
  std::string name   ; 
};


struct node{
  node_id   id   {}; 
  op_kind   kind {}; 
  value_id *inputs ;
  value_id *outputs;
};

struct graph{
  value *values; 
  node  *nodes; 
};

} //namespace
#endif 
