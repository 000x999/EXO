#include "exir/verifier.hpp"
#include <iostream>

static bool same_shape(const exir::tensor_type &left_tensor, const exir::tensor_type &right_tensor){
  return left_tensor.shape == right_tensor.shape && left_tensor.element == right_tensor.element; 
}

bool exir::verify_graph(const exir::graph &graph_in){
  bool flag          = true;
  
  const auto &values = graph_in.values(); 
  const auto &nodes  = graph_in.nodes();

  auto value_exists  = [&](exir::value_id id) -> bool{
    return id < values.size(); 
  }; 

  for(const node &n : nodes){
    for(exir::value_id input : n.inputs){
      if(!value_exists(input)){
        std::cerr << "::EXIR VERIFIER:: Node %" << n.id 
                  << " has invalid input value %" << input << "\n"; 
        flag = false; 
      }
    }

    for(exir::value_id output : n.outputs){
      if(!value_exists(output)){
        std::cerr << "::EXIR VERIFIER:: Node %" << n.id
                  << " has invalid output value %" << output << "\n"; 
        flag = false; 
      }
    }
    
    if(!flag){ continue; }

    switch(n.kind){
      case exir::op_kind::input:{
        if(n.inputs.size() != 0 || n.outputs.size() != 1){
          std::cerr << "::EXIR VERIFIER:: input node %" << n.id 
                    << " must have 0 inputs and 1 output\n"; 
          flag = false;
        }
        break; 
      }

      case exir::op_kind::constant:{
        if(n.inputs.size() != 0 || n.outputs.size() != 1){
          std::cerr << "::EXIR VERIFIER:: constant node %" << n.id
                    << " must have 0 inputs and 1 output\n"; 
          flag = false; 
        }
        break; 
      }
      case exir::op_kind::linear:{
        if(n.inputs.size() != 2 || n.outputs.size() != 1){
          std::cerr << "::EXIR VERIFIER:: linear node %" << n.id 
                    << " must have 2 inputs and 1 output\n";
          flag = false;
          break;
        }
        
        const value &input_x  = values[n.inputs [0]]; 
        const value &input_w  = values[n.inputs [1]]; 
        const value &output_y = values[n.outputs[0]];

        if(input_x.type.shape.size() != 2 || input_w.type.shape.size() != 2 || output_y.type.shape.size() != 2){
          std::cerr << "::EXIR VERIFIER:: linear node %" << n.id 
                    << " expects rank-2 tensors\n";
          flag = false;
          break; 
        }
        
        const auto batch            = input_x.type.shape[0]; 
        const auto input_features   = input_x.type.shape[1];

        const auto w_input_features = input_w.type.shape[0]; 
        const auto output_features  = input_w.type.shape[1]; 

        if(input_features != w_input_features){
          std::cerr << "::EXIR VERIFIER:: linear node %"    << n.id 
                    << " shape mismatch :: input features " << input_features
                    << " != weight input_features " << w_input_features << "\n"; 
          flag = false; 
        }

        if(output_y.type.shape[0] != batch || output_y.type.shape[1] != output_features){
          std::cerr << "::EXIR VERIFIER:: linear node %" << n.id 
                    << " output shape should be <" << batch << "x" << output_features << ">\n";
          flag = false;
        }

        break; 
      }

      case exir::op_kind::relu:{
        if(n.inputs.size() != 1 || n.outputs.size() != 1){
          std::cerr << "::EXIR VERIFIER:: relu node %" << n.id 
                    << " must have 1 input and 1 output\n";
          flag = false; 
          break; 
        }

        const value &input_x  = values[n.inputs [0]]; 
        const value &output_y = values[n.outputs[0]];

        if(!same_shape(input_x.type, output_y.type)){
          std::cerr << "::EXIR VERIFIER:: relu node %" << n.id 
                    << " input/output shapes must match\n"; 
          flag = false; 
        }

        break; 
      }

      case exir::op_kind::output:{
        if(n.inputs.size() != 1 || n.outputs.size() != 1){
          std::cerr << "::EXIR VERIFIER:: output node %" << n.id 
                    << " must have 1 input and 1 output\n";
          flag = false; 
          break; 
        }

        const value &input_x  = values[n.inputs [0]]; 
        const value &output_y = values[n.outputs[0]];

        if(!same_shape(input_x.type, output_y.type)){
          std::cerr << "::EXIR VERIFIER:: output node %" << n.id
                    << " input/output shapes must match\n";
          flag = false; 
        }
        break; 
      }
    }
  }
  return flag; 
}
