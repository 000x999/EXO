#include "exir/graph.hpp"
#include <stdexcept> 
#include <iostream>

exir::value_id exir::graph::add_value(exir::tensor_type type, std::string name){
  exir::value_id current_id = static_cast<exir::value_id>(graph_values.size());

  graph_values.push_back(value{
    .id   = current_id, 
    .type = std::move(type), 
    .name = std::move(name)
  });

  return current_id; 
}

exir::node_id exir::graph::add_node(op_kind kind, std::vector<value_id> inputs, std::vector<value_id> outputs, std::string name){
  exir::node_id current_id = static_cast<exir::node_id> (graph_nodes.size()); 

  for(exir::value_id input : inputs){
    if(input >= graph_values.size()){
      throw std::runtime_error("EXIR GRAPH ERROR :: Node input value does not exist."); 
    }
  }

  for(value_id output : outputs){
    if(output >= graph_values.size()){
      throw std::runtime_error("EXIR GRAPH ERROR :: Node output value does not exist."); 
    }
  }

  graph_nodes.push_back(node{
    .id      = current_id, 
    .kind    = kind, 
    .inputs  = std::move(inputs), 
    .outputs = std::move(outputs), 
    .name    = std::move(name)
  }); 

  return current_id; 
}

const char *exir::to_string(exir::dtype type){
  switch(type){
    case exir::dtype::float32: return "float32"; 
    case exir::dtype::int8:    return "int8"; 
    case exir::dtype::uint8:   return "uint8"; 
    case exir::dtype::int32:   return "int32"; 
  }

  return "UNK_TYPE";
}

const char *exir::to_string(exir::op_kind kind){
  switch(kind){
    case exir::op_kind::input:    return "input"; 
    case exir::op_kind::constant: return "constant"; 
    case exir::op_kind::linear:   return "linear"; 
    case exir::op_kind::relu:     return "relu"; 
    case exir::op_kind::output:   return "output"; 
  }

  return "UNK_KIND";
}


const std::vector<exir::value> &exir::graph::values() const{
  return graph_values; 
}

const std::vector<exir::node> &exir::graph::nodes() const {
  return graph_nodes; 
}


void exir::graph::print() const{
  std::cout << "=== EXIR Graph ===\n";

  for (const node& n : graph_nodes) {
    std::cout << "%" << n.id << " = " << to_string(n.kind);

    if (!n.name.empty()) {
      std::cout << " \"" << n.name << "\"";
    }

    std::cout << "(";

    for (size_t i = 0; i < n.inputs.size(); ++i) {
      std::cout << "%" << n.inputs[i];

      if (i + 1 < n.inputs.size()) {
        std::cout << ", ";
      }
    }

    std::cout << ") -> ";

    for (size_t i = 0; i < n.outputs.size(); ++i) {
      value_id out_id = n.outputs[i];

      const value& out = graph_values.at(out_id);

      std::cout << "%" << out.id;

      if (!out.name.empty()) {
        std::cout << ":" << out.name;
      }

      std::cout << " tensor<";

      for (size_t d = 0; d < out.type.shape.size(); ++d) {
        std::cout << out.type.shape[d];

        if (d + 1 < out.type.shape.size()) {
          std::cout << "x";
        }
      }

      std::cout << "x" << to_string(out.type.element) << ">";

      if (i + 1 < n.outputs.size()) {
        std::cout << ", ";
      }
    }

    std::cout << "\n";
  }
}

