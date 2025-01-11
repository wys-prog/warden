#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "strings.hpp"
#include "instructions.hpp"

namespace wylma {
  namespace warden {

    instruction parse_instruction(const std::vector<std::string> &instructions) {
      instruction myins;
      bool next_is_input = false;
      bool next_is_output = false;
      bool next_is_password = false;

      for (const auto ins : instructions) {
        if (next_is_input) {
          myins.inputs.push_back(ins);
          next_is_input = false;
          continue;
        } else if (next_is_output) {
          myins.outputs.push_back(ins);
          next_is_output = false;
          continue;
        } else if (next_is_password) {
          myins.password = ins;
          next_is_password = false;
          continue;
        }

        if (ins == "-c") {
          myins.operation = crypt;
        } else if (ins == "-i") {
          next_is_input = true;
        } else if (ins == "-o") {
          next_is_output = true;
        } else if (ins == "-p") {
          next_is_password = true;
        } else {
          std::cerr << "error: Unknown symbol: " << ins << std::endl;
        }
      }

      return myins;
    }

    std::vector<instruction> parse_file(const std::string &path) {
      std::vector<instruction> me;
      std::ifstream file(path);

      if (!file)
        throw std::runtime_error("No such file: " + path);

      std::string line;
      while (std::getline(file, line, ';')) {
        me.push_back(parse_instruction(strings::split_arguments(line)));
      }

      return me;
    }
  } // namespace warden
} // namespace wylma