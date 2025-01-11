#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "strings.hpp"
#include "instructions.hpp"
#include "parser.hpp"
#include "compiler.hpp"
#include "nodes.hpp"


int main(int argc, char *const argv[]) {
  std::cout << "Warden 1.0\n";

  std::vector<std::string> instructions, inputs;
  std::vector<wylma::warden::node> nodes;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-f") {
      inputs.push_back(std::string(argv[++i]));
    } else {
      instructions.push_back(argv[i]);
    }
  }

  for (size_t i = 0; i < instructions.size(); i++) {
    wylma::warden::node n;

    n.id = "main@" + std::to_string(i);
    n.ins = wylma::warden::parse_instruction(wylma::warden::strings::split_arguments(instructions[i]));

    nodes.push_back(n);
  }

  for (const auto &input : inputs) {
    auto vn = wylma::warden::get_nodes_from_file(input);
    nodes.insert(nodes.end(), vn.begin(), vn.end());
  }

  for (const auto &node : nodes) {
    wylma::warden::compile_nodes(nodes);
  }

  return 0;
}