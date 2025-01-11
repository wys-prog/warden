#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

#include "warden.hpp"
#include "instructions.hpp"
#include "parser.hpp"
#include "compiler.hpp"



int main(int argc, char *const argv[]) {
  std::vector<std::string> instructions, inputs;

  for (int i = 1; i < argc; i++) {
    if (std::string(argv[i]) == "-f") {
      inputs.push_back(std::string(argv[++i]));
    } else {
      instructions.push_back(argv[i]);
    }
  }



  return 0;
}