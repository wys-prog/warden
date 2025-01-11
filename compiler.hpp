#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "warden.hpp"

#include "instructions.hpp"
#include "nodes.hpp"
#include "strings.hpp"

namespace wylma {
  namespace warden {

    std::string get_file(std::vector<std::string> &inputs) {
      std::string file_name = "WardenProcess_" + strings::get_rand();
      std::ofstream out(file_name, std::ios::binary);

      for (const auto &input : inputs) {
        std::ifstream file(input, std::ios::binary);
        if (!file)
          throw std::runtime_error("No such file: " + input);

        char buffer[512];
        while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
          out.write(buffer, file.gcount());
        }
      }

      return file_name;
    }

    void write_outputs(const std::vector<std::string> &outs,
                      const std::string &in) {
      std::ifstream input(in, std::ios::binary);
      if (!input)
        throw std::runtime_error("No such file: " + in);

      std::vector<std::ofstream> output_files;
      for (const auto &out : outs) {
        output_files.emplace_back(out, std::ios::binary);
        if (!output_files.back())
          throw std::runtime_error("Cannot open output file: " + out);
      }

      char buffer[512];
      while (input.read(buffer, sizeof(buffer)) || input.gcount() > 0) {
        for (auto &file : output_files) {
          file.write(buffer, input.gcount());
        }
      }
    }

    void compile(node &my_node) {
      std::cout << "Warden: Compiling node: " << my_node.id << ".\n"
                << "      | Password: " << my_node.ins.password << "\n"
                << "      | Inputs:   "
                << strings::compile(my_node.ins.inputs, " · ") << "\n"
                << "      | Outputs:  "
                << strings::compile(my_node.ins.outputs, " · ") << "\n";

      crypter c(my_node.ins.password);

      // Generate temporary input and output files
      std::string input_name = get_file(my_node.ins.inputs);
      std::string output_name = "WardenProcess_" + strings::get_rand() + "_TMP";

      try {
        std::ifstream input(input_name, std::ios::binary);
        std::ofstream output(output_name, std::ios::binary);

        if (!input || !output)
          throw std::runtime_error("Failed to open temporary files.");

        if (my_node.ins.operation == crypt) {
          c.crypt(input, output);
        } else {
          c.decrypt(input, output);
        }

        input.close();
        output.close();

        write_outputs(my_node.ins.outputs, output_name);

        // Clean up temporary files
        std::remove(input_name.c_str());
        std::remove(output_name.c_str());

        std::cout << "Warden: Compilation of node: " << my_node.id
                  << " is finished.\n";

      } catch (...) {
        // Ensure temporary files are cleaned up in case of errors
        std::remove(input_name.c_str());
        std::remove(output_name.c_str());
        throw;
      }
    }

    void compile_nodes(const std::vector<node> &nodes) {
      for (auto n : nodes) {
        compile(n);
      }
    }

  } // namespace warden

} // namespace wylma