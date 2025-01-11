#pragma once

#include <string>

#include "instructions.hpp"

namespace wylma {

  namespace warden {

    typedef struct node {
      std::string id;
      instruction ins;
    };
    
  }

}