#include <filesystem>
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

namespace fs = std::filesystem;

std::vector<std::string> get_files(const std::string &directory = "./")
{
  std::vector<std::string> files;
  try
  {
    for (const auto &entry : fs::directory_iterator(directory))
    {
      if (entry.is_regular_file())
      {
        std::string extension = entry.path().extension().string();
        if (extension == ".wa" || extension == ".warden")
        {
          files.push_back(entry.path().string());
          std::cout << "file found: " << entry.path().string() << std::endl;
        }
      }
    }
  }
  catch (const fs::filesystem_error &e)
  {
    std::cerr << "Error accessing directory: " << e.what() << '\n';
  }
  return files;
}

int main(int argc, char *const argv[])
{
  std::cout << "Warden 1.0\n";

  std::vector<std::string> instructions, inputs;
  std::vector<wylma::warden::node> nodes;

  for (int i = 1; i < argc; i++)
  {
    if (std::string(argv[i]) == "-f")
    {
      inputs.push_back(std::string(argv[++i]));
    }
    else
    {
      instructions.push_back(argv[i]);
    }
  }

  // Get all .wa and .warden files
  std::vector<std::string> found_files = get_files();
  inputs.insert(inputs.end(), found_files.begin(), found_files.end());

  for (size_t i = 0; i < instructions.size(); i++)
  {
    wylma::warden::node n;
    n.id = "main@" + std::to_string(i);
    n.ins = wylma::warden::parse_instruction(wylma::warden::strings::split_arguments(instructions[i]));
    nodes.push_back(n);
  }

  for (const auto &input : inputs)
  {
    auto vn = wylma::warden::get_nodes_from_file(input);
    nodes.insert(nodes.end(), vn.begin(), vn.end());
  }

  for (const auto &node : nodes)
  {
    wylma::warden::compile_nodes(nodes);
  }

  return 0;
}
