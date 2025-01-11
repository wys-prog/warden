#pragma once

#include <string>

#include "instructions.hpp"

namespace wylma {

  namespace warden {

    typedef struct {
      std::string id;
      instruction ins;
    } node;
    
  }

}