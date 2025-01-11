#pragma once

#include <ctime>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

namespace wylma {
  namespace warden {

    class strings {
    public:
      static std::string compile(const std::string &str) {
        return str;
      }

      template <typename T>
      static std::string compile(const T &t) {
        return std::to_string(t);
      }

      template <typename T>
      static std::string compile(const std::vector<T> &vec, const std::string &end = "") {
        std::string mystring;

        for (const auto &elem : vec) {
          mystring += compile(elem) + end;
        }

        return mystring;
      }

      static std::vector<std::string> split_arguments(const std::string &args) {
        std::vector<std::string> myargs;
        std::string              myarg;

        bool in_quots = false;

        for (const auto &c : args) {
          if (c == '"') {
            in_quots = !in_quots;

            // Skip the quote character itself
            continue;
          }

          if (!in_quots && (c == ' ' || c == '\t' || c == '\n')) {
            // Push the current argument if not empty
            if (!myarg.empty()) {
              myargs.push_back(myarg);
              myarg.clear();
            }
            continue;
          }

          // Append the character to the current argument
          myarg.push_back(c);
        }

        // Add the last argument if any
        if (!myarg.empty()) {
          myargs.push_back(myarg);
        }

        return myargs;
      }

      static void trim(std::string &str) {
        size_t beg = 0;
        size_t end = str.size();
        
        while (beg < end && isspace(str[beg])) {
          ++beg;
        }
        
        while (end > beg && isspace(str[end - 1])) {
          --end;
        }
        
        str = str.substr(beg, end - beg);
      }

      static std::string get_rand() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d%m%Y%H%M%S");
        return oss.str();
      }
    };
  }

}