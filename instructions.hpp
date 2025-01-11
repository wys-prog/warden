#pragma once

#include <vector>
#include <string>

namespace wylma {
  namespace warden {

    enum op {
      crypt,
      decrypt
    };

    typedef struct {
      op                       operation;
      std::vector<std::string> inputs;
      std::vector<std::string> outputs;
      std::string              password;
    } instruction;

  }
}