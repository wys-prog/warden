#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#include "warden.hpp"

#include "nodes.hpp"
#include "strings.hpp"
#include "instructions.hpp"

namespace wylma {
  namespace warden {

    void compile(node &my_node) {
      std::cout << "Warden: Compiling node: " << my_node.id << ".\n"
                   "      | Password: " << my_node.ins.password << "\n"
                   "      | Inputs:   " << strings::compile(my_node.ins.inputs, ", ") << "\n"
                   "      | Outputs:  " << strings::compile(my_node.ins.outputs, ", ") << "\n";
      
      crypter c(my_node.ins.password);
      
      for (const auto &input : my_node.ins.inputs) {
        std::ifstream in(input);

        if (!in) throw std::runtime_error("Warden: No such file: " + input);

        for (const auto &output : my_node.ins.outputs) {
          std::ofstream out(output);

          if (!out) throw std::runtime_error("Warden: No such file: " + output);

          if (my_node.ins.operation == crypt) {
            c.crypt(in, out);
          } else {
            c.decrypt(in, out);
          }

          out.close();
        }

        in.close();
      }

      std::cout << "Warden: Compilation of node: " << my_node.id << " is finished.\n";
    }

    void compile_nodes(const std::vector<node> &nodes) {
      for (auto n : nodes) {
        compile(n);
      }
    }

  }

}