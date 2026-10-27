#ifndef GRAPH_HPP
#define GRAPH_HPP 

#include <cstdint> 
#include <string> 
#include <vector> 

namespace exir{
enum class dtype{
  float32, 
  int8, 
  uint8, 
  int32,
};

enum class op_kind{
  input, 
  constant, 
  linear, 
  relu, 
  output
}; 

struct tensor_type{
  std::vector<int64_t> shape;
  dtype                element = dtype::float32; 
}; 

using value_id = uint32_t; 
using node_id  = uint32_t; 

struct value{
  value_id    id   {}; // uint32_t identifier
  tensor_type type {}; // shape (vector) + dtype (f32)
  std::string name   ; 
};


struct node{
  node_id               id   {}; 
  op_kind               kind {}; 
  std::vector<value_id> inputs ; // vector of uint32_t for inputs 
  std::vector<value_id> outputs; // vector of uint32_t for outputs
  std::string           name = ""; 
};

class graph{
public:
  value_id add_value (tensor_type type, std::string name = ""); 
  node_id  add_node  (op_kind kind    , std::vector<value_id> inputs, std::vector<value_id> outputs, std::string name = "");

  const std::vector<value> &values() const; // vector of uint32_t identifiers
  const std::vector<node>  &nodes () const;

  void  mutate_node               (exir::node_id id_in , std::string new_name);
  void  mutate_value              (exir::value_id id_in, std::string new_name);
  
  void  print                     () const; 
  bool  validate_shape            () const; 

private:
  std::vector<value> graph_values; 
  std::vector<node>  graph_nodes; 
};

const char *to_string (dtype   type);
const char *to_string (op_kind kind); 

} //namespace
#endif 
