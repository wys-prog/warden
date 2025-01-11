#pragma once


#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "nodes.hpp"
#include "strings.hpp"
#include "instructions.hpp"

namespace wylma {
  namespace warden {

    instruction parse_instruction(const std::vector<std::string> &instructions) {
      instruction myins;

      for (size_t i = 0; i < instructions.size(); ++i) {
        if (instructions[i] == "-c") {
          myins.operation = crypt;
        } else if (instructions[i] == "-d") {
          myins.operation = decrypt;
        } else if (instructions[i] == "-i") {
          if (i + 1 < instructions.size()) {
            myins.inputs.push_back(instructions[++i]);
          } else {
            throw std::runtime_error("Error: Missing input file after '-i'");
          }
        } else if (instructions[i] == "-o") {
          if (i + 1 < instructions.size()) {
            myins.outputs.push_back(instructions[++i]);
          } else {
            throw std::runtime_error("Error: Missing output file after '-o'");
          }
        } else {
          // Check if the argument is unrecognized
          if (instructions[i].starts_with("-")) {
            throw std::runtime_error("Error: Unknown option " + instructions[i]);
          }
          // Otherwise, treat it as a password
          myins.password = instructions[i];
        }
      }

      return myins;
    }



    std::vector<node> get_nodes_from_file(const std::string &path) {
      std::vector<node> nodes;
      std::ifstream input(path);
      if (!input) throw std::runtime_error("Warden: No such file: " + path);

      std::string line;

      while (std::getline(input, line)) { 
        strings::trim(line);
        node n;

        if (line.starts_with("$") && line.ends_with(":")) {
          size_t beg = line.find('$'), end = line.find(':', beg + 1);
          if (beg == std::string::npos || end == std::string::npos) throw std::runtime_error("Warden: Parse error\nLine: " + line); 

          n.id = line.substr(beg + 1, end - (beg + 1));

          std::getline(input, line);

          while (line.empty()) {
            std::getline(input, line);
            strings::trim(line);
          }

        } else if (line.empty()) continue; else {
          n.id = strings::get_rand();
        }

        n.ins = parse_instruction(strings::split_arguments(line));

        nodes.push_back(n);
      }

      return nodes;
    }

  } // namespace warden
} // namespace wylma